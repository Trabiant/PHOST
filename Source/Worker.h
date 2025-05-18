#pragma once
#include "Config.h"
#include "ImageData.h"
#include <QObject>
#include <spdlog/spdlog.h>
#include <opencv2/core/utils/logger.hpp>
#include <QMessageBox>

class Worker : public QObject {
    Q_OBJECT
public:
    Worker(const cv::Mat& mask_, Config cfg,
           std::vector<std::vector<ImageData>> packages,
           QObject* parent = nullptr);

public slots:
    void process();
    void stop();

signals:
    void statusUpdate(const QString &text);
    void estimationUpdate(const QString &text);
    void error(const QString &what);
    void finished();
    void progressBarUpdate(int value);
    void progressBarShow();
    void progressBarHide();

private:
    std::atomic<bool> m_abort;
    Config currentConfig;
    std::vector<std::vector<ImageData>> packages;
    cv::Mat mask;
};
