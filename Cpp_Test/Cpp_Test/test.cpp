#include <iostream>
#include <QApplication>
#include <QWidget>
class Test
{
public:
    Test(QWidget* ui = nullptr) {}
    void show() { ui->show(); }
    int count() const { return m_count; }
private:
    QWidget* ui;
    int m_count = 0;
};
void showTest(const Test& t)
{
    std::cout << t.count() << std::endl;
    t.show();
}
int main(int argc, char* argv[])
{
    //QApplication a(argc, argv);
    void* w;
    Test t(w);
    showTest(t);
    return a.exec();
}
