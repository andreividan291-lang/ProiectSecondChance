#include "secondchance.h"
#include "./ui_secondchance.h"

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

    createProductTitleLineEdit       = ui->CreateTitleBox;
    createProductDescriptionLineEdit = ui->CreateTitleDescription;
    createProductPriceLineEdit       = ui->CreateTitlePrice;
    createProductCategoryLineEdit    = ui->CreateTitleCategory;
    createProductLocationLineEdit    = ui->CreateTitleLocation;
    createProductDateLineEdit        = ui->CreateTitleDate;

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
    connectClearOnType(createProductDateLineEdit);

    // ── Răspunsuri asincrone de la Server ────────────────────────────────────
    connect(&ServerManager::get_instance(), &ServerManager::loginResult,
            this, [this](bool success, QString msg) {
                if (success) {
                    ui->stackedWidget->setCurrentWidget(ui->PaginaPrincipalaMagazinClient);
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
                    // Curățăm câmpurile după înregistrare reușită
                    emailLineEdit->clear();
                    parolaLineEdit->clear();
                    numeLineEdit->clear();
                    prenumeLineEdit->clear();
                    nrTelefonLineEdit->clear();
                    bioLineEdit->clear();
                    ui->stackedWidget->setCurrentWidget(ui->SignInClient);
                } else {
                    ui->StatusSignUpLabelSU->setText("✘ " + msg);
                    ui->StatusSignUpLabelSU->setStyleSheet("color: red;");
                    setFieldError(emailLineEdit, "Email-ul poate fi deja folosit");
                }
            });

    connect(&ServerManager::get_instance(), &ServerManager::adminLoginResult,
            this, [this](bool success, QString msg) {
                if (success) {
                    ui->stackedWidget->setCurrentWidget(ui->AdminAppPage);
                    ui->StatusSignUpLabelSignIn_Admin->clear();
                } else {
                    ui->StatusSignUpLabelSignIn_Admin->setText("✘ Date admin incorecte!");
                    ui->StatusSignUpLabelSignIn_Admin->setStyleSheet("color: red;");
                    setFieldError(emailLineEdit_admin);
                    setFieldError(parolaLineEdit_admin);
                    setFieldError(codPersonalEdit_admin, "Verificați codul personal");
                }
            });

    // ── Pagina inițială ───────────────────────────────────────────────────────
    ui->stackedWidget->setCurrentWidget(ui->ChooseAccountTypePage);

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
    ServerManager& sm = ServerManager::get_instance();

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

// ─── Acțiuni butoane ─────────────────────────────────────────────────────────
void SecondChance::on_SignIntoAppButton_clicked()
{
    if (!validateSignInFields()) return;

    ServerManager::get_instance().checkLoginUtilizator(
        signInEmailEdit->text().trimmed(),
        signInParolaEdit->text()
        );
    ui->stackedWidget->setCurrentWidget(ui->PaginaPrincipalaMagazinClient);
}

void SecondChance::on_SignUpIntoApp_clicked()
{
    if (!validateSignUpFields()) return;

    ServerManager::get_instance().registerClient(
        ServerManager::get_instance().get_userIndexInApp(),
        emailLineEdit->text().trimmed(),
        parolaLineEdit->text(),
        numeLineEdit->text().trimmed(),
        prenumeLineEdit->text().trimmed(),
        nrTelefonLineEdit->text().trimmed(),
        bioLineEdit->text().trimmed()
        );
    ui->stackedWidget->setCurrentWidget(ui->PaginaPrincipalaMagazinClient);
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

    qDebug() << "[Qt] Produs nou:"
             << "Titlu:"    << createProductTitleLineEdit->text()
             << "Pret:"     << createProductPriceLineEdit->text()
             << "Categorie:" << createProductCategoryLineEdit->text()
             << "Locatie:"  << createProductLocationLineEdit->text();

    // TODO: trimite produsul la server când implementezi acea funcționalitate
}

// ─── Navigare ─────────────────────────────────────────────────────────────────
void SecondChance::on_SignInButton_clicked()            { ui->stackedWidget->setCurrentWidget(ui->SignIn_UpPageClient); }
void SecondChance::on_SignUpButton_clicked()            { ui->stackedWidget->setCurrentWidget(ui->ChooseAccountTypePage); }
void SecondChance::on_SignInClientButton_clicked()      { ui->stackedWidget->setCurrentWidget(ui->SignInClient); }
void SecondChance::on_SignUpClientButton_clicked()      { ui->stackedWidget->setCurrentWidget(ui->SignUpClient); }
void SecondChance::on_ChooseClientTypeButton_clicked()  { ui->stackedWidget->setCurrentWidget(ui->SignIn_UpPageClient); }
void SecondChance::on_BackButtonSU_clicked()            { ui->stackedWidget->setCurrentWidget(ui->SignIn_UpPageClient); }
void SecondChance::on_BackButtonSI_clicked()            { ui->stackedWidget->setCurrentWidget(ui->SignIn_UpPageClient); }
void SecondChance::on_ChooseAdminClientButton_clicked() { ui->stackedWidget->setCurrentWidget(ui->AdminSignInUpPage); }
void SecondChance::on_AdminSignInButton_clicked()       { ui->stackedWidget->setCurrentWidget(ui->AdminSignInPage); }
void SecondChance::on_BackToUserType_clicked()          { ui->stackedWidget->setCurrentWidget(ui->ChooseAccountTypePage); }
void SecondChance::on_BackButtonSI_Admin_clicked()      { ui->stackedWidget->setCurrentWidget(ui->ChooseAccountTypePage); }
void SecondChance::on_FromAdminSignInToAccountType_clicked() { ui->stackedWidget->setCurrentWidget(ui->ChooseAccountTypePage); }
void SecondChance::on_Create_Product_clicked()          { ui->stackedWidget->setCurrentWidget(ui->Interface_Create_Product); }
void SecondChance::on_pushButton_clicked()              { ui->stackedWidget->setCurrentWidget(ui->SignUpClient); }

// ─── Focus handlers (păstrate pentru compatibilitate cu header-ul) ────────────
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
void SecondChance::onCreateProductDateReturnPressed()        { createProductDateLineEdit->clearFocus(); }

SecondChance::~SecondChance() { delete ui; }
