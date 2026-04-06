#include "secondchance.h"
#include "./ui_secondchance.h"
#include "utilizator.h"
#include "servermanager.h"

SecondChance::SecondChance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SecondChance)
{
    ui->setupUi(this);

    // Pagina initiala
    ui->stackedWidget->setCurrentWidget(ui->ChooseAccountTypePage);

    // Legaturi UI
    emailLineEdit = ui->InsertEmailBoxSU;
    parolaLineEdit = ui->InsertPasswordBoxSU;
    numeLineEdit = ui->InsertNumeBoxSU;
    prenumeLineEdit = ui->InsertPrenumeBoxSU;
    nrTelefonLineEdit = ui->InsertNrTelefonBoxSU;
    bioLineEdit = ui->InsertBioBoxSU;

    signInEmailEdit = ui->InsertEmailBoxSI;
    signInParolaEdit = ui->InsertPasswordBoxSi;

    emailLineEdit_admin = ui->InsertEmailBoxSI_Admin;
    parolaLineEdit_admin = ui->InsertPasswordBoxSi_Admin;
    codPersonalEdit_admin = ui->InsertPersonalCodeBox;

    // Connecturi - SIGN UP
    connect(emailLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onEmailReturnPressed);
    connect(parolaLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onParolaReturnPressed);
    connect(numeLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onNumeReturnPressed);
    connect(prenumeLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onPrenumeReturnPressed);
    connect(nrTelefonLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onNrTelefonReturnPressed);
    connect(bioLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onBioReturnPressed);

    // Connecturi - SIGN IN
    connect(signInEmailEdit, &QLineEdit::returnPressed, this, &SecondChance::onSignInEmailReturnPressed);
    connect(signInParolaEdit, &QLineEdit::returnPressed, this, &SecondChance::onSignInPasswordPressed);

    // Connecturi - ADMIN
    connect(emailLineEdit_admin, &QLineEdit::returnPressed, this, &SecondChance::onEmailAdminReturnPressed);
    connect(parolaLineEdit_admin, &QLineEdit::returnPressed, this, &SecondChance::onParolaAdminEmailPressed);
    connect(codPersonalEdit_admin, &QLineEdit::returnPressed, this, &SecondChance::onCodPersonalEmailPressed);
}

SecondChance::~SecondChance()
{
    delete ui;
}

//
// ================= NAVIGARE =================
//

void SecondChance::on_SignInButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->SignIn_UpPageClient);
}

void SecondChance::on_SignUpButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->ChooseAccountTypePage);
}

void SecondChance::on_SignInClientButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->SignInClient);
}

void SecondChance::on_SignUpClientButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->SignUpClient);
}

void SecondChance::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->SignUpClient);
}

void SecondChance::on_ChooseClientTypeButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->SignIn_UpPageClient);
}

void SecondChance::on_BackButtonSU_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->SignIn_UpPageClient);
}

void SecondChance::on_BackButtonSI_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->SignIn_UpPageClient);
}

void SecondChance::on_ChooseAdminClientButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->AdminSignInUpPage);
}

void SecondChance::on_AdminSignInButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->AdminSignInPage);
}

//
// ================= RETURN PRESSED =================
//

void SecondChance::onEmailReturnPressed()
{
    emailLineEdit->clearFocus();
}

void SecondChance::onParolaReturnPressed()
{
    parolaLineEdit->clearFocus();
}

void SecondChance::onNumeReturnPressed()
{
    numeLineEdit->clearFocus();
}

void SecondChance::onPrenumeReturnPressed()
{
    prenumeLineEdit->clearFocus();
}

void SecondChance::onNrTelefonReturnPressed()
{
    nrTelefonLineEdit->clearFocus();
}

void SecondChance::onBioReturnPressed()
{
    bioLineEdit->clearFocus();
}

void SecondChance::onSignInEmailReturnPressed()
{
    signInEmailEdit->clearFocus();
}

void SecondChance::onSignInPasswordPressed()
{
    signInParolaEdit->clearFocus();
}

void SecondChance::onEmailAdminReturnPressed()
{
    emailLineEdit_admin->clearFocus();
}

void SecondChance::onParolaAdminEmailPressed()
{
    parolaLineEdit_admin->clearFocus();
}

void SecondChance::onCodPersonalEmailPressed()
{
    codPersonalEdit_admin->clearFocus();
}

//
// ================= SIGN IN =================
//

void SecondChance::on_SignIntoAppButton_clicked()
{
    try {
        QString email = signInEmailEdit->text().trimmed().remove(QRegularExpression("\\s"));
        QString parola = signInParolaEdit->text().trimmed().remove(QRegularExpression("\\s"));

        if (email.isEmpty() || parola.isEmpty()) {
            throw MyException("Te rog completează toate câmpurile!");
        }

        bool loginValid = ServerManager::get_instance().checkLogin(email, parola);

        if (!loginValid) {
            throw MyException("Contul nu există sau parola este greșită!");
        }

        ui->stackedWidget->setCurrentWidget(ui->PaginaPrincipalaMagazinClient);
        ui->StatusSignUpLabelSignIn->clear();

    } catch (const MyException& ex) {
        ui->StatusSignUpLabelSignIn->setText(ex.what());
        ui->StatusSignUpLabelSignIn->setStyleSheet("color: red;");
    } catch (const std::exception& ex) {
        ui->StatusSignUpLabelSignIn->setText("A apărut o eroare neașteptată!");
        ui->StatusSignUpLabelSignIn->setStyleSheet("color: red;");
        qDebug() << ex.what();
    }
}

//
// ================= SIGN UP =================
//

void SecondChance::on_SignUpIntoApp_clicked()
{
    QString email = emailLineEdit->text().trimmed();
    QString parola = parolaLineEdit->text().trimmed();
    QString nume = numeLineEdit->text().trimmed();
    QString prenume = prenumeLineEdit->text().trimmed();
    QString nrTel = nrTelefonLineEdit->text().trimmed();
    QString bio = bioLineEdit->text().trimmed();

    if (email.isEmpty() || parola.isEmpty() || nume.isEmpty() || prenume.isEmpty() || nrTel.isEmpty()) {
        ui->StatusSignUpLabelSU->setText("Toate câmpurile trebuie completate!");
        ui->StatusSignUpLabelSU->setStyleSheet("color: red;");
        return;
    }

    if (!email.contains("@") || !email.contains(".")) {
        ui->StatusSignUpLabelSU->setText("Email invalid!");
        ui->StatusSignUpLabelSU->setStyleSheet("color: red;");
        return;
    }

    if (!ServerManager::get_instance().numeValid(nume)) {
        ui->StatusSignUpLabelSU->setText("Nume invalid!");
        ui->StatusSignUpLabelSU->setStyleSheet("color: red;");
        return;
    }

    if (!ServerManager::get_instance().prenumeValid(prenume)) {
        ui->StatusSignUpLabelSU->setText("Prenume invalid!");
        ui->StatusSignUpLabelSU->setStyleSheet("color: red;");
        return;
    }

    if (!ServerManager::get_instance().telefonValid(nrTel)) {
        ui->StatusSignUpLabelSU->setText("Număr telefon invalid!");
        ui->StatusSignUpLabelSU->setStyleSheet("color: red;");
        return;
    }

    if (!ServerManager::get_instance().bioValid(bio)) {
        ui->StatusSignUpLabelSU->setText("Bio prea lung! (max 200)");
        ui->StatusSignUpLabelSU->setStyleSheet("color: red;");
        return;
    }

    bool success = ServerManager::get_instance().registerClient(
        ServerManager::get_instance().get_userIndexInApp(),
        email, parola, nume, prenume, nrTel, bio
        );

    if (success) {
        ui->StatusSignUpLabelSU->setText("User creat cu succes!");
        ui->StatusSignUpLabelSU->setStyleSheet("color: green;");
        ui->stackedWidget->setCurrentWidget(ui->PaginaPrincipalaMagazinClient);
    } else {
        ui->StatusSignUpLabelSU->setText("Email-ul există deja sau eroare!");
        ui->StatusSignUpLabelSU->setStyleSheet("color: red;");
    }
}
