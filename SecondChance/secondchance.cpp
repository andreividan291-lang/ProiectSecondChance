#include "secondchance.h"
#include "./ui_secondchance.h"
#include "utilizator.h"
#include "servermanager.h"

SecondChance::SecondChance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SecondChance)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page);

    emailLineEdit = ui->InsertEmailBox;
    parolaLineEdit = ui->InsertPasswordBox;
    numeLineEdit = ui->InsertNumeBox;
    prenumeLineEdit = ui->InsertPrenumeBox;
    nrTelefonLineEdit = ui ->InsertNrTelefonBox;
    bioLineEdit = ui->InsertBioBox;
    signInEmailEdit = ui->SignInEmailBox;
    signInParolaEdit = ui->SignInPasswordBox;


    connect(emailLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onEmailReturnPressed);
    connect(parolaLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onParolaReturnPressed);
    connect(numeLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onNumeReturnPressed);
    connect(prenumeLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onPrenumeReturnPressed);
    connect(nrTelefonLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onNrTelefonReturnPressed);
    connect(bioLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onBioReturnPressed);
    connect(signInEmailEdit, &QLineEdit::returnPressed, this, &SecondChance::onSignInEmailReturnPressed);
    connect(signInParolaEdit, &QLineEdit::returnPressed, this, &SecondChance::onSignInPasswordPressed);

}

SecondChance::~SecondChance()
{
    delete ui;
}

void SecondChance::on_LogInButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void SecondChance::on_SignUpButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void SecondChance::onEmailReturnPressed() {
    QString text = emailLineEdit->text();
    emailLineEdit->clearFocus();
}

void SecondChance::onParolaReturnPressed() {
    QString text = parolaLineEdit->text();
    parolaLineEdit->clearFocus();
}

void SecondChance::onNumeReturnPressed()
{
    QString text = parolaLineEdit->text();
    parolaLineEdit->clearFocus();
}

void SecondChance::onPrenumeReturnPressed()
{
    QString text = parolaLineEdit->text();
    parolaLineEdit->clearFocus();
}

void SecondChance::onNrTelefonReturnPressed()
{
    QString text = parolaLineEdit->text();
    parolaLineEdit->clearFocus();
}
void SecondChance::onBioReturnPressed()
{
    QString text = parolaLineEdit->text();
    parolaLineEdit->clearFocus();
}

void SecondChance::onSignInEmailReturnPressed()
{
    QString text = signInEmailEdit->text();
    parolaLineEdit->clearFocus();
}

void SecondChance::onSignInPasswordPressed()
{
    QString text = signInParolaEdit->text();
    parolaLineEdit->clearFocus();
}


void SecondChance::on_DoneButton_clicked()
{
    QString email = emailLineEdit->text();
    QString parola = parolaLineEdit->text();
    QString nume = numeLineEdit->text();
    QString prenume = prenumeLineEdit->text();
    QString nrTel = nrTelefonLineEdit->text();
    QString bio = bioLineEdit->text();



    int pozAt = email.indexOf("@");
    QString dupaAt = email.mid(pozAt + 1);

    if (!email.contains("@") || (pozAt == 0 || pozAt == email.length() - 1) || (!dupaAt.contains("."))) {
        ui->StatusSignUpLabelSignUp->setText("Email invalid!");
        ui->StatusSignUpLabelSignUp->setStyleSheet("color: red;");
        return;
    }

    if(email.isEmpty() || parola.isEmpty() || nume.isEmpty() || prenume.isEmpty() || nrTel.isEmpty()) {
        ui->StatusSignUpLabelSignUp->setText("Toate câmpurile trebuie completate!");
        ui->StatusSignUpLabelSignUp->setStyleSheet("color: red;");
        return;
    }

    if(!ServerManager::get_instance().numeValid(nume))
    {
        ui->StatusSignUpLabelSignUp->setText("Nume invalid!");
        ui->StatusSignUpLabelSignUp->setStyleSheet("color: red;");
        return;
    }

    if(!ServerManager::get_instance().prenumeValid(prenume))
    {
        ui->StatusSignUpLabelSignUp->setText("Nume invalid!");
        ui->StatusSignUpLabelSignUp->setStyleSheet("color: red;");
        return;
    }

    if(!ServerManager::get_instance().telefonValid(nrTel))
    {
        ui->StatusSignUpLabelSignUp->setText("Numar telefon invalid!");
        ui->StatusSignUpLabelSignUp->setStyleSheet("color: red;");
        return;
    }

    if(!ServerManager::get_instance().bioValid(bio))
    {
        ui->StatusSignUpLabelSignUp->setText("Bio prea lung! (max200)");
        ui->StatusSignUpLabelSignUp->setStyleSheet("color: red;");
        return;
    }

    bool success = ServerManager::get_instance().registerUser(email, parola,nume, prenume,nrTel, bio);

    if(success) {
        ui->StatusSignUpLabelSignUp->setText("User creat cu succes!");
        ui->StatusSignUpLabelSignUp->setStyleSheet("color: green;");
        ui->stackedWidget->setCurrentWidget(ui->page_4);
    } else {
        ui->StatusSignUpLabelSignUp->setText("Email-ul există deja sau a apărut o eroare!");
        ui->StatusSignUpLabelSignUp->setStyleSheet("color: red;");
    }
}

void SecondChance::on_SignInAppButton_clicked()
{
    try {
        // 1️⃣ Preluăm valorile din QLineEdit și le curățăm
        QString email = signInEmailEdit->text().trimmed().remove(QRegularExpression("\\s"));
        QString parola = signInParolaEdit->text().trimmed().remove(QRegularExpression("\\s"));

        // 2️⃣ Validări simple înainte de interogare
        if (email.isEmpty() || parola.isEmpty()) {
            throw MyException("Te rog completează toate câmpurile!");
        }

        // 3️⃣ Verificăm login-ul în baza de date
        bool loginValid = ServerManager::get_instance().checkLogin(email, parola);

        if (!loginValid) {
            // Dacă nu există contul, aruncăm excepție
            throw MyException("Contul nu există sau parola este greșită!");
        }

        // 4️⃣ Dacă login-ul e valid, trecem la pagina principală
        ui->stackedWidget->setCurrentWidget(ui->page_4);
        ui->StatusSignUpLabelSignIn->clear(); // curățăm mesajul de eroare

    } catch (const MyException& ex) {
        // 5️⃣ Prindem excepția și afișăm mesajul în label
        ui->StatusSignUpLabelSignIn->setText(ex.what());
        ui->StatusSignUpLabelSignIn->setStyleSheet("color: red;");
    } catch (const std::exception& ex) {
        // 6️⃣ Alte erori neașteptate
        ui->StatusSignUpLabelSignIn->setText("A apărut o eroare neașteptată!");
        ui->StatusSignUpLabelSignIn->setStyleSheet("color: red;");
        qDebug() << "Eroare neașteptată:" << ex.what();
    }
}
