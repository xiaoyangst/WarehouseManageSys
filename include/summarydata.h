//
// Created by xy on 2024-06-06.
//

#ifndef WAREHOUSEMANAGESYS__SUMMARYDATA_H_
#define WAREHOUSEMANAGESYS__SUMMARYDATA_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SummaryData; }
QT_END_NAMESPACE

class SummaryData : public QWidget {
 Q_OBJECT

 public:
  explicit SummaryData(QWidget *parent = nullptr);
  ~SummaryData() override;

 private:
  Ui::SummaryData *ui;
};

#endif //WAREHOUSEMANAGESYS__SUMMARYDATA_H_
