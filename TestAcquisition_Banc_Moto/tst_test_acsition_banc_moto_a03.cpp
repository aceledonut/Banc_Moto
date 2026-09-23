#include <QtTest>

// add necessary includes here

class Test_Acsition_Banc_Moto_A03 : public QObject
{
    Q_OBJECT

public:
    Test_Acsition_Banc_Moto_A03();
    ~Test_Acsition_Banc_Moto_A03();

private slots:
    void test_case1();
};

Test_Acsition_Banc_Moto_A03::Test_Acsition_Banc_Moto_A03() {}

Test_Acsition_Banc_Moto_A03::~Test_Acsition_Banc_Moto_A03() {}

void Test_Acsition_Banc_Moto_A03::test_case1() {}

QTEST_APPLESS_MAIN(Test_Acsition_Banc_Moto_A03)

#include "tst_test_acsition_banc_moto_a03.moc"
