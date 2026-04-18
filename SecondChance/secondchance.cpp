#include "secondchance.h"
#include "./ui_secondchance.h"
#include <QFileInfo>
// ─── Stiluri ──────────────────────────────────────────────────────────────────
static const QString STYLE_ERROR = "border: 1px solid red; border-radius: 4px;";
static const QString STYLE_OK    = "border: 1px solid green; border-radius: 4px;";
static const QString STYLE_RESET = "";

// ─── Constructor ──────────────────────────────────────────────────────────────
SecondChance::SecondChance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SecondChance)
{
    ui->setupUi(this);

    // Conectare la serverul VS
    if (!ServerManager::get_instance().start_server(1234)) {
        qDebug() << "[Qt] Nu s-a putut conecta la server!";
    }

    // ── Inițializare pointeri UI ──────────────────────────────────────────────
    emailLineEdit         = ui->InsertEmailBoxSU;
    parolaLineEdit        = ui->InsertPasswordBoxSU;
    numeLineEdit          = ui->InsertNumeBoxSU;
    prenumeLineEdit       = ui->InsertPrenumeBoxSU;
    nrTelefonLineEdit     = ui->InsertNrTelefonBoxSU;
    bioLineEdit           = ui->InsertBioBoxSU;
    signInEmailEdit       = ui->InsertEmailBoxSI;
    signInParolaEdit      = ui->InsertPasswordBoxSi;
    emailLineEdit_admin   = ui->InsertEmailBoxSI_Admin;
    parolaLineEdit_admin  = ui->InsertPasswordBoxSi_Admin;
    codPersonalEdit_admin = ui->InsertPersonalCodeBox;
    insertNewSumOfMoney   = ui->InsertNewSumOfMoneyLine;
    insertNewMailLine     = ui->InsertNewMailLine;
    insertNewPasswordLine = ui->InsertNewPasswordLine;

    createProductTitleLineEdit       = ui->CreateTitleBox;
    createProductDescriptionLineEdit = ui->CreateTitleDescription;
    createProductPriceLineEdit       = ui->CreateTitlePrice;
    createProductCategoryLineEdit    = ui->CreateTitleCategory;
    createProductLocationLineEdit    = ui->CreateTitleLocation;
    createProductConditionLineEdit   = ui->CreateTitleCondition;

    // ── Parole ascunse ────────────────────────────────────────────────────────
    parolaLineEdit->setEchoMode(QLineEdit::Password);
    signInParolaEdit->setEchoMode(QLineEdit::Password);
    parolaLineEdit_admin->setEchoMode(QLineEdit::Password);

    // ── Ștergere erori vizuale când userul modifică câmpul ───────────────────
    connectClearOnType(emailLineEdit);
    connectClearOnType(parolaLineEdit);
    connectClearOnType(numeLineEdit);
    connectClearOnType(prenumeLineEdit);
    connectClearOnType(nrTelefonLineEdit);
    connectClearOnType(bioLineEdit);
    connectClearOnType(signInEmailEdit);
    connectClearOnType(signInParolaEdit);
    connectClearOnType(emailLineEdit_admin);
    connectClearOnType(parolaLineEdit_admin);
    connectClearOnType(codPersonalEdit_admin);
    connectClearOnType(createProductTitleLineEdit);
    connectClearOnType(createProductDescriptionLineEdit);
    connectClearOnType(createProductPriceLineEdit);
    connectClearOnType(createProductCategoryLineEdit);
    connectClearOnType(createProductLocationLineEdit);
    connectClearOnType(createProductConditionLineEdit);
    connectClearOnType(insertNewSumOfMoney);
    connectClearOnType(insertNewMailLine);
    connectClearOnType(insertNewPasswordLine);

    // ── Răspunsuri asincrone de la Server ────────────────────────────────────
    connect(&ServerManager::get_instance(), &ServerManager::loginResult,
            this, [this](bool success, QString msg, int userId) {
                if (success) {
                    idUtilizatorLogat = userId; // salvăm id-ul real din baza de date
                    qDebug() << "[Qt] Utilizator logat cu ID:" << idUtilizatorLogat;
                    ui->ProductDetailPage->setCurrentWidget(ui->PaginaPrincipalaMagazinClient);
                    ui->StatusSignUpLabelSignIn->clear();
                    setFieldOk(signInEmailEdit);
                    setFieldOk(signInParolaEdit);
                } else {
                    ui->StatusSignUpLabelSignIn->setText("Email sau parolă incorecte!");
                    ui->StatusSignUpLabelSignIn->setStyleSheet("color: red;");
                    setFieldError(signInEmailEdit);
                    setFieldError(signInParolaEdit, "Verificați datele introduse");
                }
            });

    connect(&ServerManager::get_instance(), &ServerManager::registerResult,
            this, [this](bool success, QString msg) {
                if (success) {
                    ui->StatusSignUpLabelSU->setText("✔ Cont creat cu succes!");
                    ui->StatusSignUpLabelSU->setStyleSheet("color: green;");
                    emailLineEdit->clear();
                    parolaLineEdit->clear();
                    numeLineEdit->clear();
                    prenumeLineEdit->clear();
                    nrTelefonLineEdit->clear();
                    bioLineEdit->clear();
                    ui->ProductDetailPage->setCurrentWidget(ui->PaginaPrincipalaMagazinClient);
                } else {
                    ui->StatusSignUpLabelSU->setText("✘ " + msg);
                    ui->StatusSignUpLabelSU->setStyleSheet("color: red;");
                    setFieldError(emailLineEdit, "Email-ul poate fi deja folosit");
                }
            });

    connect(&ServerManager::get_instance(), &ServerManager::adminLoginResult,
            this, [this](bool success, QString msg) {
                if (success) {
                    ui->ProductDetailPage->setCurrentWidget(ui->AdminAppPage);
                    ui->StatusSignUpLabelSignIn_Admin->clear();
                } else {
                    ui->StatusSignUpLabelSignIn_Admin->setText("✘ Date admin incorecte!");
                    ui->StatusSignUpLabelSignIn_Admin->setStyleSheet("color: red;");
                    setFieldError(emailLineEdit_admin);
                    setFieldError(parolaLineEdit_admin);
                    setFieldError(codPersonalEdit_admin, "Verificați codul personal");
                }
            });

    connect(&ServerManager::get_instance(), &ServerManager::adaugaProdusResult,
            this, [this](bool success, QString msg, int idProdus) {
                ui->CreateProductDoneButton->setEnabled(true);
                if (success) {
                    ui->StatusCreateProduct->setText(
                        "✔ Produs adăugat cu succes! (ID: " + QString::number(idProdus) + ")"
                        );
                    ui->StatusCreateProduct->setStyleSheet("color: green;");

                    // Curatam campurile
                    createProductTitleLineEdit->clear();
                    createProductDescriptionLineEdit->clear();
                    createProductPriceLineEdit->clear();
                    createProductCategoryLineEdit->clear();
                    createProductLocationLineEdit->clear();
                    createProductConditionLineEdit->clear();
                    calePozaSelectata.clear();
                    // Navigam inapoi dupa 1.5s
                    QTimer::singleShot(1500, this, [this]() {
                        ui->ProductDetailPage->setCurrentWidget(ui->PaginaPrincipalaMagazinClient);
                        ui->StatusCreateProduct->clear();
                    });
                } else {
                    ui->StatusCreateProduct->setText("✘ " + msg);
                    ui->StatusCreateProduct->setStyleSheet("color: red;");
                }
            });

    connect(&ServerManager::get_instance(), &ServerManager::alimentarePortofelResult,
            this, [this](bool success, QString msg, double soldNou) {
                if (success) {
                    ui->FillWalletErrorLabel->setStyleSheet("color: green;");
                    ui->FillWalletErrorLabel->setText(
                        "✔ Portofel alimentat! Sold nou: " + QString::number(soldNou, 'f', 2) + " RON"
                        );
                    insertNewSumOfMoney->clear();
                } else {
                    ui->FillWalletErrorLabel->setStyleSheet("color: red;");
                    ui->FillWalletErrorLabel->setText("✘ " + msg);
                }
            });

    connect(&ServerManager::get_instance(), &ServerManager::schimbareMailResult,
            this, [this](bool success, QString msg) {
                if (success) {
                    ui->ChangeEmailErrorLabel->setStyleSheet("color: green;");
                    ui->ChangeEmailErrorLabel->setText("✔ Email schimbat cu succes!");
                    insertNewMailLine->clear();
                } else {
                    ui->ChangeEmailErrorLabel->setStyleSheet("color: red;");
                    ui->ChangeEmailErrorLabel->setText("✘ " + msg);
                    setFieldError(insertNewMailLine, "Email invalid sau deja folosit");
                }
            });

    connect(&ServerManager::get_instance(), &ServerManager::schimbareParolaResult,
            this, [this](bool success, QString msg) {
                if (success) {
                    ui->ChangePasswordDoneButton->setEnabled(true);
                    ui->ChangePasswordErrorButton->setStyleSheet("color: green;");
                    ui->ChangePasswordErrorButton->setText("✔ Parolă schimbată cu succes!");
                    insertNewPasswordLine->clear();
                } else {
                    ui->ChangePasswordDoneButton->setEnabled(true);
                    ui->ChangePasswordErrorButton->setStyleSheet("color: red;");
                    ui->ChangePasswordErrorButton->setText("✘ " + msg);
                    setFieldError(insertNewPasswordLine, "Eroare la schimbarea parolei");
                }
            });

    // ── Pagina inițială ───────────────────────────────────────────────────────
    ui->ProductDetailPage->setCurrentWidget(ui->ChooseAccountTypePage);

    // ── Return pressed (focus) ────────────────────────────────────────────────
    connect(emailLineEdit,     &QLineEdit::returnPressed, parolaLineEdit,    qOverload<>(&QLineEdit::setFocus));
    connect(parolaLineEdit,    &QLineEdit::returnPressed, numeLineEdit,      qOverload<>(&QLineEdit::setFocus));
    connect(numeLineEdit,      &QLineEdit::returnPressed, prenumeLineEdit,   qOverload<>(&QLineEdit::setFocus));
    connect(prenumeLineEdit,   &QLineEdit::returnPressed, nrTelefonLineEdit, qOverload<>(&QLineEdit::setFocus));
    connect(nrTelefonLineEdit, &QLineEdit::returnPressed, bioLineEdit,       qOverload<>(&QLineEdit::setFocus));
    connect(signInEmailEdit,   &QLineEdit::returnPressed, signInParolaEdit,  qOverload<>(&QLineEdit::setFocus));
    connect(signInParolaEdit,  &QLineEdit::returnPressed, this, &SecondChance::on_SignIntoAppButton_clicked);
    connect(emailLineEdit_admin,   &QLineEdit::returnPressed, parolaLineEdit_admin,  qOverload<>(&QLineEdit::setFocus));
    connect(parolaLineEdit_admin,  &QLineEdit::returnPressed, codPersonalEdit_admin, qOverload<>(&QLineEdit::setFocus));
    connect(codPersonalEdit_admin, &QLineEdit::returnPressed, this, &SecondChance::on_SignIntoAppButton_Admin_clicked);
    connect(insertNewSumOfMoney, &QLineEdit::returnPressed, this, &SecondChance::insertNewSumOfMoneyPressed);

}

// ─── Helper-e vizuale ─────────────────────────────────────────────────────────
void SecondChance::setFieldError(QLineEdit* field, const QString& tooltip) {
    field->setStyleSheet(STYLE_ERROR);
    if (!tooltip.isEmpty()) field->setToolTip(tooltip);
}

void SecondChance::setFieldOk(QLineEdit* field) {
    field->setStyleSheet(STYLE_OK);
    field->setToolTip("");
}

void SecondChance::clearFieldState(QLineEdit* field) {
    field->setStyleSheet(STYLE_RESET);
    field->setToolTip("");
}

void SecondChance::connectClearOnType(QLineEdit* field) {
    connect(field, &QLineEdit::textChanged, this, [this, field]() {
        clearFieldState(field);
    });
}

// ─── Validări ─────────────────────────────────────────────────────────────────
bool SecondChance::validateSignInFields() {
    bool ok = true;
    if (signInEmailEdit->text().trimmed().isEmpty()) {
        setFieldError(signInEmailEdit, "Introduceți email-ul");
        ok = false;
    }
    if (signInParolaEdit->text().isEmpty()) {
        setFieldError(signInParolaEdit, "Introduceți parola");
        ok = false;
    }
    if (!ok)
        ui->StatusSignUpLabelSignIn->setText("Completați toate câmpurile!");
    else
        ui->StatusSignUpLabelSignIn->clear();
    return ok;
}

bool SecondChance::validateSignUpFields() {
    bool ok = true;
    ServerManager& sm = ServerManager::get_instance();

    if (emailLineEdit->text().trimmed().isEmpty()) {
        setFieldError(emailLineEdit, "Email obligatoriu");
        ok = false;
    }
    if (parolaLineEdit->text().length() < 6) {
        setFieldError(parolaLineEdit, "Parola trebuie să aibă minim 6 caractere");
        ok = false;
    }
    if (!sm.numeValid(numeLineEdit->text().trimmed())) {
        setFieldError(numeLineEdit, "Numele poate conține doar litere");
        ok = false;
    }
    if (!sm.prenumeValid(prenumeLineEdit->text().trimmed())) {
        setFieldError(prenumeLineEdit, "Prenumele poate conține doar litere");
        ok = false;
    }
    if (!sm.telefonValid(nrTelefonLineEdit->text().trimmed())) {
        setFieldError(nrTelefonLineEdit, "Număr de telefon invalid (minim 10 cifre)");
        ok = false;
    }
    if (!sm.bioValid(bioLineEdit->text())) {
        setFieldError(bioLineEdit, "Bio-ul poate avea maxim 200 de caractere");
        ok = false;
    }
    if (!ok)
        ui->StatusSignUpLabelSU->setText("Verificați câmpurile marcate cu roșu!");
    else
        ui->StatusSignUpLabelSU->clear();
    return ok;
}

bool SecondChance::validateAdminFields() {
    bool ok = true;
    if (emailLineEdit_admin->text().trimmed().isEmpty()) {
        setFieldError(emailLineEdit_admin, "Email obligatoriu");
        ok = false;
    }
    if (parolaLineEdit_admin->text().isEmpty()) {
        setFieldError(parolaLineEdit_admin, "Parolă obligatorie");
        ok = false;
    }
    if (codPersonalEdit_admin->text().trimmed().isEmpty()) {
        setFieldError(codPersonalEdit_admin, "Cod personal obligatoriu");
        ok = false;
    }
    if (!ok)
        ui->StatusSignUpLabelSignIn_Admin->setText("Completați toate câmpurile!");
    else
        ui->StatusSignUpLabelSignIn_Admin->clear();
    return ok;
}

bool SecondChance::validateProductFields() {
    bool ok = true;
    if (createProductTitleLineEdit->text().trimmed().isEmpty()) {
        setFieldError(createProductTitleLineEdit, "Titlul este obligatoriu");
        ok = false;
    }
    if (createProductPriceLineEdit->text().trimmed().isEmpty()) {
        setFieldError(createProductPriceLineEdit, "Prețul este obligatoriu");
        ok = false;
    } else {
        bool isDouble;
        double price = createProductPriceLineEdit->text().toDouble(&isDouble);
        if (!isDouble || price <= 0) {
            setFieldError(createProductPriceLineEdit, "Introduceți un preț valid (ex: 49.99)");
            ok = false;
        }
    }
    if (createProductCategoryLineEdit->text().trimmed().isEmpty()) {
        setFieldError(createProductCategoryLineEdit, "Categoria este obligatorie");
        ok = false;
    }
    if (createProductLocationLineEdit->text().trimmed().isEmpty()) {
        setFieldError(createProductLocationLineEdit, "Locația este obligatorie");
        ok = false;
    }
    return ok;
}

// ─── Acțiuni butoane ──────────────────────────────────────────────────────────
void SecondChance::on_SignIntoAppButton_clicked()
{
    if (!validateSignInFields()) return;

    ServerManager::get_instance().checkLoginUtilizator(
        signInEmailEdit->text().trimmed(),
        signInParolaEdit->text()
        );
}

void SecondChance::on_SignUpIntoApp_clicked()
{
    if (!validateSignUpFields()) return;
    ServerManager::get_instance().registerClient(
        emailLineEdit->text().trimmed(),
        parolaLineEdit->text(),
        numeLineEdit->text().trimmed(),
        prenumeLineEdit->text().trimmed(),
        nrTelefonLineEdit->text().trimmed(),
        bioLineEdit->text().trimmed()
        );
}

void SecondChance::on_SignIntoAppButton_Admin_clicked()
{
    if (!validateAdminFields()) return;
    ServerManager::get_instance().checkLoginAdmin(
        emailLineEdit_admin->text().trimmed(),
        parolaLineEdit_admin->text(),
        codPersonalEdit_admin->text().trimmed()
        );
}

void SecondChance::on_CreateProductDoneButton_clicked()
{
    if (!validateProductFields()) return;

    // Dezactivam butonul pana vine raspunsul (evita dublu-click)
    ui->CreateProductDoneButton->setEnabled(false);

    ServerManager::get_instance().adaugaProdus(
        idUtilizatorLogat,
        createProductTitleLineEdit->text().trimmed(),
        createProductDescriptionLineEdit->text().trimmed(),  // optional
        calePozaSelectata,                                   // gol daca nu a selectat
        createProductPriceLineEdit->text().toDouble(),                                                   // stoc default 1
        createProductCategoryLineEdit->text().trimmed(),
        createProductConditionLineEdit->text().trimmed()                                               // stare default
        );

}

// ─── Navigare ─────────────────────────────────────────────────────────────────
void SecondChance::on_SignInButton_clicked()            { ui->ProductDetailPage->setCurrentWidget(ui->SignIn_UpPageClient); }
void SecondChance::on_SignUpButton_clicked()            { ui->ProductDetailPage->setCurrentWidget(ui->ChooseAccountTypePage); }
void SecondChance::on_SignInClientButton_clicked()      { ui->ProductDetailPage->setCurrentWidget(ui->SignInClient); }
void SecondChance::on_SignUpClientButton_clicked()      { ui->ProductDetailPage->setCurrentWidget(ui->SignUpClient); }
void SecondChance::on_ChooseClientTypeButton_clicked()  { ui->ProductDetailPage->setCurrentWidget(ui->SignIn_UpPageClient); }
void SecondChance::on_BackButtonSU_clicked()            { ui->ProductDetailPage->setCurrentWidget(ui->SignIn_UpPageClient); }
void SecondChance::on_BackButtonSI_clicked()            { ui->ProductDetailPage->setCurrentWidget(ui->SignIn_UpPageClient); }
void SecondChance::on_ChooseAdminClientButton_clicked() { ui->ProductDetailPage->setCurrentWidget(ui->AdminSignInUpPage); }
void SecondChance::on_AdminSignInButton_clicked()       { ui->ProductDetailPage->setCurrentWidget(ui->AdminSignInPage); }
void SecondChance::on_BackToUserType_clicked()          { ui->ProductDetailPage->setCurrentWidget(ui->ChooseAccountTypePage); }
void SecondChance::on_BackButtonSI_Admin_clicked()      { ui->ProductDetailPage->setCurrentWidget(ui->ChooseAccountTypePage); }
void SecondChance::on_FromAdminSignInToAccountType_clicked() { ui->ProductDetailPage->setCurrentWidget(ui->ChooseAccountTypePage); }
void SecondChance::on_Create_Product_clicked()          { ui->ProductDetailPage->setCurrentWidget(ui->Interface_Create_Product); }
void SecondChance::on_pushButton_clicked()              { ui->ProductDetailPage->setCurrentWidget(ui->SignUpClient); }

// ─── Focus handlers ───────────────────────────────────────────────────────────
void SecondChance::onEmailReturnPressed()                    { emailLineEdit->clearFocus(); }
void SecondChance::onParolaReturnPressed()                   { parolaLineEdit->clearFocus(); }
void SecondChance::onNumeReturnPressed()                     { numeLineEdit->clearFocus(); }
void SecondChance::onPrenumeReturnPressed()                  { prenumeLineEdit->clearFocus(); }
void SecondChance::onNrTelefonReturnPressed()                { nrTelefonLineEdit->clearFocus(); }
void SecondChance::onBioReturnPressed()                      { bioLineEdit->clearFocus(); }
void SecondChance::onSignInEmailReturnPressed()              { signInEmailEdit->clearFocus(); }
void SecondChance::onEmailAdminReturnPressed()               { emailLineEdit_admin->clearFocus(); }
void SecondChance::onParolaAdminEmailPressed()               { parolaLineEdit_admin->clearFocus(); }
void SecondChance::onCodPersonalEmailPressed()               { codPersonalEdit_admin->clearFocus(); }
void SecondChance::onCreateProductTitleReturnPressed()       { createProductTitleLineEdit->clearFocus(); }
void SecondChance::onCreateProductDescriptionReturnPressed() { createProductDescriptionLineEdit->clearFocus(); }
void SecondChance::onCreateProductPriceReturnPressed()       { createProductPriceLineEdit->clearFocus(); }
void SecondChance::onCreateProductCategoryReturnPressed()    { createProductCategoryLineEdit->clearFocus(); }
void SecondChance::onCreateProductLocationReturnPressed()    { createProductLocationLineEdit->clearFocus(); }
void SecondChance::onCreateProductConditionReturnPressed()        { createProductConditionLineEdit->clearFocus(); }
void SecondChance::insertNewSumOfMoneyPressed(){ insertNewSumOfMoney->clear(); }

SecondChance::~SecondChance() { delete ui; }

void SecondChance::on_ToSettingsPushButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->SettingsClient);
}


void SecondChance::on_ToMyProductsPushButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->MyProductsPage);
}



void SecondChance::on_ToMyFavoriteProducts_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->FavoritesPage);
}


void SecondChance::on_ToMyAccountPushButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->MyAccountPage);
}


void SecondChance::on_ToChangeMailPagePushButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->ChangeMailPage);
}


void SecondChance::on_ToChangePasswordPagePushButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->ChangePasswordPage);
}


void SecondChance::on_FromFillWalletToSettingsBackButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->SettingsClient);
}


void SecondChance::on_FromFavoritesToSettingsBackButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->SettingsClient);
}


void SecondChance::on_FromMyProductsToSettingsBackButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->SettingsClient);
}

void SecondChance::on_FromSettingsToSettingsBackButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->SettingsClient);
}



void SecondChance::on_FillWalletDoneButton_clicked()
{
    QString sumaText = insertNewSumOfMoney->text().trimmed();
    if (sumaText.isEmpty()) {
        ui->FillWalletErrorLabel->setStyleSheet("color: red;");
        ui->FillWalletErrorLabel->setText("✘ Introduceți o sumă!");
        return;
    }

    bool ok;
    double suma = sumaText.toDouble(&ok);
    if (!ok || suma <= 0) {
        ui->FillWalletErrorLabel->setStyleSheet("color: red;");
        ui->FillWalletErrorLabel->setText("✘ Sumă invalidă (ex: 50.00)");
        setFieldError(insertNewSumOfMoney, "Introduceți o sumă validă");
        return;
    }

    ui->FillWalletErrorLabel->clear();
    ServerManager::get_instance().alimenteazaPortofel(idUtilizatorLogat, suma);
}

void SecondChance::on_ChangeEmailDoneButton_clicked()
{
    QString emailNou = insertNewMailLine->text().trimmed();
    if (emailNou.isEmpty()) {
        ui->ChangeEmailErrorLabel->setStyleSheet("color: red;");
        ui->ChangeEmailErrorLabel->setText("✘ Introduceți noul email!");
        setFieldError(insertNewMailLine, "Email obligatoriu");
        return;
    }

    ui->ChangeEmailErrorLabel->clear();
    ServerManager::get_instance().schimbaMail(idUtilizatorLogat, emailNou);
}

void SecondChance::on_ChangePasswordDoneButton_clicked()
{
    QString parolaNova = insertNewPasswordLine->text();

    if (parolaNova.isEmpty()) {
        ui->ChangePasswordErrorButton->setStyleSheet("color: red;");
        ui->ChangePasswordErrorButton->setText("✘ Introduceți noua parolă!");
        setFieldError(insertNewPasswordLine, "Parolă obligatorie");
        return;
    }
    if (parolaNova.length() < 6) {
        ui->ChangePasswordErrorButton->setStyleSheet("color: red;");
        ui->ChangePasswordErrorButton->setText("✘ Parola trebuie să aibă minim 6 caractere!");
        setFieldError(insertNewPasswordLine, "Minim 6 caractere");
        return;
    }

    ui->ChangePasswordDoneButton->setEnabled(false);
    ui->ChangePasswordErrorButton->clear();
    ServerManager::get_instance().schimbaParola(idUtilizatorLogat, parolaNova);
}


void SecondChance::on_FillWalletPushButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->FillWalletPage);
}


void SecondChance::on_FromChangePasswordBackButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->SettingsClient);
}


void SecondChance::on_FromChangeEmailBackButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->SettingsClient);
}


void SecondChance::on_FromCreateProductBackButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->PaginaPrincipalaMagazinClient);
}


void SecondChance::on_FromMyAccountBackButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->PaginaPrincipalaMagazinClient);
}


void SecondChance::on_ChoosePicturePushButton_clicked()
{
    QString cale = QFileDialog::getOpenFileName(
        this,
        "Selectează o poză",
        QDir::homePath(),
        "Imagini (*.png *.jpg *.jpeg *.bmp *.webp)"
        );

    if (cale.isEmpty()) return; // userul a anulat

    calePozaSelectata = cale;

    // Afișăm numele fișierului selectat pe buton
    ui->ChoosePicturePushButton->setText("✔ " + QFileInfo(cale).fileName());
}
