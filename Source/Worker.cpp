#include "Worker.h"
#include "DatasetManager.h"
#include "CameraPositionManager.h"
#include "TextureGenerator.h"
#include "RCProcessLauncher.h"
#include "ProgressManager.h"
#include <QObject>
#include <spdlog/spdlog.h>
#include <opencv2/core/utils/logger.hpp>
#include <QMessageBox>

Worker::Worker(const cv::Mat& mask_, Config cfg,
    std::vector<std::vector<ImageData>> packages, QObject* parent)
    : QObject(parent), mask(mask_), currentConfig(std::move(cfg)),
    packages(std::move(packages)), m_abort(false)
{}

void Worker::process() {
    try {
        // Настройка логирования: шаблон сообщения и отключение OpenCV-лога
        spdlog::set_pattern("[%H:%M:%S.%e] %^[PHOST]%$ %v");
        cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
        // Проверка: если отмена задана до начала — выходим
        if (m_abort.load()) { emit finished(); return; }
        // Менеджер датасета — сортирует и валидирует изображения
        DatasetManager datasetMng(
            currentConfig.datasetPath,
            currentConfig.baseCount,
            currentConfig.psImageCount);

        if (m_abort.load()) { emit finished(); return; }
        // Инициализация менеджера поз камер из CSV (в зависимости от имени проекта)
        CameraPositionManager camPosMng(
            (currentConfig.datasetPath.parent_path() /
                "ProjectFiles" / "RC" /
                (currentConfig.projectName + ".csv")).string());

        if (m_abort.load()) { emit finished(); return; }
        // Создание генератора текстур, передаём маску и позиции камер
        TextureGenerator texGen(
            currentConfig.datasetPath.parent_path(),
            mask,
            currentConfig.baseCount,
            camPosMng);

        for (auto& pkg : packages) {
            if (m_abort.load()) break;
            try {
                emit statusUpdate(tr("Preparing base color..."));
                texGen.PrepareBaseColor(pkg);
            }
            catch (const std::exception& e) {
                spdlog::warn("Package {} skipped: {}",
                            pkg[0].filename, e.what());
                emit error(QString::fromStdString(e.what()));
            }
        }
        // Если в конфигурации включён запуск RC — запускаем реконструкцию
        if (!m_abort.load() && currentConfig.launchRC) {
            emit statusUpdate(tr("Mesh Reconstruction"));
            RCProcessLauncher rcLaunch(
                currentConfig.rcPath,
                texGen,
                currentConfig.datasetPath.parent_path(),
                currentConfig.projectName);
            rcLaunch.ExecuteCommand(
                rcLaunch.BuildModelCommand(currentConfig.quality));
        }

        if (!m_abort.load()) {
            emit statusUpdate(tr("Texture Processing"));
            emit progressBarShow();
            camPosMng.LoadPositions();
            // Регистрируем и выводим прогресс обработки
            ProgressManager prog_mng(packages.size());
            for (size_t i = 0; i < packages.size(); ++i) {
                if (m_abort.load()) break;

                prog_mng.StartIterationTracking();
                // Пропускаем пакет, если позиция камеры не найдена
                if (!camPosMng.GetCameraPosition(packages[i][0].filename)) {
                    packages[i].clear();
                    packages[i].shrink_to_fit();
                    prog_mng.FinishIterationTracking();
                    continue;
                }
                // Основная обработка текстур: normal, roughness
                texGen.ProcessTextures(
                    packages[i],
                    currentConfig.useDirectX_NormalMap);
                prog_mng.FinishIterationTracking();

                auto elapsed = ProgressManager::Format_Duration(
                    prog_mng.GetElapsedTime());
                auto remain  = ProgressManager::Format_Duration(
                    prog_mng.GetRemainingTime());
                emit estimationUpdate(
                    QString("Elapsed: %1   Remaining: %2")
                        .arg(QString::fromStdString(elapsed))
                        .arg(QString::fromStdString(remain)));
                emit progressBarUpdate(
                    static_cast<int>(prog_mng.GetProgress() * 100));
            }
            emit progressBarHide();
            emit progressBarUpdate(100);
            emit statusUpdate(tr(""));

        }

        if (!m_abort.load() && currentConfig.launchRC) {
            emit statusUpdate(tr("Texturing Model"));
            emit estimationUpdate("");
            RCProcessLauncher rcLaunch(
                currentConfig.rcPath,
                texGen,
                currentConfig.datasetPath.parent_path(),
                currentConfig.projectName);
            rcLaunch.ExecuteCommand(
                rcLaunch.BuildTextureCommand());
        }
        spdlog::info("Worker finished successfully");
        emit statusUpdate(tr("Finished"));
        emit estimationUpdate("");
        emit progressBarHide();
        emit finished();
    }
    catch (const std::exception& ex) {
        emit error(QString("Error: %1")
                        .arg(QString::fromStdString(ex.what())));
        emit statusUpdate(tr(""));
        emit progressBarHide();
        emit estimationUpdate("");
        emit finished();
    }
}
void Worker::stop() {
    m_abort.store(true);
}
