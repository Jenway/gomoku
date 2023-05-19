#include "history.h"
#include "ui_history.h"

int restart::RESTART_SEEK;

History::History(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::History)
{

    ui->setupUi(this);
    this->setWindowTitle("History");
    QFile goData("gameRecord.csv");
    int temp = 0;
    QString line;
    if (goData.open(QIODevice::ReadOnly)) {
        this->ui->treeWidget->setColumnCount(6);
        this->ui->treeWidget->setHeaderLabels(QStringList() << "编号/持子"
                                                            << "X/模式"
                                                            << "Y/赢家"
                                                            << "步数"
                                                            << "时间"
                                                            << "");

        QStringList round;
        QTreeWidgetItem* TopItem;
        for (; goData.readLine() != QString("");) {

            goData.seek(temp);
            line = goData.readLine();

            // 创建父节点
            round = QStringList(line.split(','));
            TopItem = new QTreeWidgetItem(round);
            this->ui->treeWidget->addTopLevelItem(TopItem);
            QPushButton* button = new QPushButton(this);
            button->setText(QString("对局回放"));
            button->setWhatsThis(QString::number(temp));
            //                qDebug()<<temp;
            connect(button, &QPushButton::clicked, this, &History::on_Button_clicked);

            this->ui->treeWidget->setItemWidget(TopItem, 5, button);

            temp += line.length();

            QTreeWidgetItem* childItem;
            QStringList qstrlist;
            for (; goData.read(2) != QString("->");) {
                goData.seek(temp);
                line = goData.readLine();
                temp += line.length();

                // 创建子节点
                qstrlist = QStringList(line.split(','));
                childItem = new QTreeWidgetItem(qstrlist);
                TopItem->addChild(childItem);
            }
            goData.seek(temp);
            line = goData.readLine();
            temp += line.length();
        }

        goData.close();
    }
}

History::~History()
{
    delete ui;
}

void History::on_Button_clicked()
{
    HistoryBoard* w = new HistoryBoard();
    //    QDesktopWidget dw;
    //    int x= dw.width()*VIEW_VOL;
    //    int y=dw.height()*VIEW_VOL;
    int x = 2600 * VIEW_VOL;
    int y = 1800 * VIEW_VOL;
    w->setFixedSize(x, y);

    QPushButton* pBtn = qobject_cast<QPushButton*>(sender());
    QString tag = pBtn->whatsThis();

    int RESTART = tag.toInt();
    restart::RESTART_SEEK = RESTART;
    w->i = RESTART;
    //    qDebug()<<RESTART;q
    qDebug() << restart::RESTART_SEEK;
    w->show();
}

void History::closeEvent(QCloseEvent*)
{
    delete this;
}
