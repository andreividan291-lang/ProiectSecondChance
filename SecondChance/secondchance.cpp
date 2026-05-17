#include "secondchance.h"
#include "./ui_secondchance.h"
#include <QFileInfo>
#include <QMessageBox>
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

    setupAppStyle();

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
    insertNewPasswordLine->setEchoMode(QLineEdit::Password);
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
                    idUtilizatorLogat = userId;
                    incarcaProduse();
                    ServerManager::get_instance().getNotificari(userId); // ADAUGĂ
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
            this, [this](bool success, QString msg, int userId) {  // <-- adaugă int userId
                if (success) {
                    idUtilizatorLogat = userId;  // <-- ADAUGĂ ASTA
                    qDebug() << "[Qt] Utilizator inregistrat cu ID:" << idUtilizatorLogat;

                    ui->StatusSignUpLabelSU->setText("✔ Cont creat cu succes!");
                    ui->StatusSignUpLabelSU->setStyleSheet("color: green;");
                    emailLineEdit->clear();
                    parolaLineEdit->clear();
                    numeLineEdit->clear();
                    prenumeLineEdit->clear();
                    nrTelefonLineEdit->clear();
                    bioLineEdit->clear();
                    incarcaProduse();
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

                    QString produsNou =
                        createProductTitleLineEdit->text().trimmed()
                        + " - "
                        + createProductPriceLineEdit->text().trimmed()
                        + " RON | "
                        + createProductCategoryLineEdit->text().trimmed()
                        + " | "
                        + createProductLocationLineEdit->text().trimmed()
                        + " | "
                        + createProductConditionLineEdit->text().trimmed();

                    produse.append(produsNou);

                    // Curățăm câmpurile
                    createProductTitleLineEdit->clear();
                    createProductDescriptionLineEdit->clear();
                    createProductPriceLineEdit->clear();
                    createProductCategoryLineEdit->clear();
                    createProductLocationLineEdit->clear();
                    createProductConditionLineEdit->clear();
                    calePozaSelectata.clear();

                    ui->ChoosePicturePushButton->setText("Choose Picture");

                    // Navigăm înapoi după 1.5s
                    QTimer::singleShot(1500, this, [this]() {
                        ui->ProductDetailPage->setCurrentWidget(ui->PaginaPrincipalaMagazinClient);
                        incarcaProduse();
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

    connect(&ServerManager::get_instance(), &ServerManager::produseClientResult,
            this, [this](bool success, QString msg, QJsonArray produse) {
                ui->ProductsListWidget->clear();
                idProdusSelectat = -1;

                if (!success) {
                    QMessageBox::warning(this, "Eroare", msg);
                    return;
                }

                for (const QJsonValue& val : produse) {
                    QJsonObject p = val.toObject();

                    int     id        = p["id"].toInt();
                    QString nume      = p["nume"].toString();
                    double  pret      = p["pret"].toDouble();
                    QString categorie = p["categorie"].toString();
                    QString stare     = p["stare"].toString();
                    QString vanzator  = p["vanzator"].toString();

                    QString linie = QString("%1 - %2 RON | %3 | %4 | %5")
                                        .arg(nume)
                                        .arg(pret, 0, 'f', 2)
                                        .arg(categorie)
                                        .arg(stare)
                                        .arg(vanzator);

                    QListWidgetItem* item = new QListWidgetItem(linie);
                    item->setData(Qt::UserRole,     p["id"].toInt());
                    item->setData(Qt::UserRole + 1, p["poza_cale"].toString());
                    item->setData(Qt::UserRole + 2, p["descriere"].toString());
                    item->setData(Qt::UserRole + 3, p["vanzator"].toString());
                    item->setData(Qt::UserRole + 4, p["id_vanzator"].toInt());
                    ui->ProductsListWidget->addItem(item);
                }
            });

    connect(&ServerManager::get_instance(), &ServerManager::adaugaFavoritResult,
            this, [this](bool success, QString msg) {
                if (success)
                    QMessageBox::information(this, "Favorite", "✔ Produs adăugat la favorite!");
                else
                    QMessageBox::warning(this, "Favorite", "✘ " + msg);
            });

    // ── Filtrare categorie ────────────────────────────────────────────────────
    connect(ui->checkBox_Incaltaminte, &QCheckBox::toggled,
            this, [this](bool checked) {
                if (checked) {
                    ui->checkBox_Imbracaminte->setChecked(false);
                    categorieFiltraActiva = "Incaltaminte";
                } else {
                    categorieFiltraActiva = "";
                }
                cautaProduse();
            });

    connect(ui->checkBox_Imbracaminte, &QCheckBox::toggled,
            this, [this](bool checked) {
                if (checked) {
                    ui->checkBox_Incaltaminte->setChecked(false);
                    categorieFiltraActiva = "Imbracaminte";
                } else {
                    categorieFiltraActiva = "";
                }
                cautaProduse();
            });

    connect(&ServerManager::get_instance(), &ServerManager::produseUtilizatorResult,
            this, [this](bool success, QString msg, QJsonArray produse) {
                // Curățăm lista
                QListWidget* lista = ui->MyProductsScrollContent->findChild<QListWidget*>();
                if (!lista) {
                    lista = new QListWidget(ui->MyProductsScrollContent);
                    QVBoxLayout* layout = new QVBoxLayout(ui->MyProductsScrollContent);
                    layout->addWidget(lista);
                    lista->setStyleSheet(
                        "QListWidget { background-color: white; color: #2F3640;"
                        "border: 2px solid #DCDDE1; border-radius: 10px; padding: 5px; font-size: 10pt; }"
                        "QListWidget::item { padding: 8px; border-bottom: 1px solid #DCDDE1; }"
                        "QListWidget::item:selected { background-color: #6C63FF; color: white; border-radius: 6px; }"
                        );
                }
                lista->clear();

                if (!success) {
                    QMessageBox::warning(this, "Eroare", msg);
                    return;
                }

                if (produse.isEmpty()) {
                    lista->addItem("Nu ai produse listate.");
                    return;
                }

                for (const QJsonValue& val : produse) {
                    QJsonObject p = val.toObject();
                    QString vandut = p["vandut"].toString() == "1" ? " [VÂNDUT]" : "";
                    QString linie = QString("%1 - %2 RON | %3 | %4%5")
                                        .arg(p["nume"].toString())
                                        .arg(p["pret"].toDouble(), 0, 'f', 2)
                                        .arg(p["categorie"].toString())
                                        .arg(p["stare"].toString())
                                        .arg(vandut);

                    QListWidgetItem* item = new QListWidgetItem(linie);
                    item->setData(Qt::UserRole, p["id"].toInt());
                    if (!vandut.isEmpty())
                        item->setForeground(Qt::gray);
                    lista->addItem(item);
                }
            });

    connect(&ServerManager::get_instance(), &ServerManager::getFavoriteResult,
            this, [this](bool success, QString msg, QJsonArray produse) {
                ui->FavoritesListWidget->clear();

                if (!success) {
                    QMessageBox::warning(this, "Eroare", msg);
                    return;
                }

                if (produse.isEmpty()) {
                    ui->FavoritesListWidget->addItem("Nu ai produse favorite.");
                    return;
                }

                for (const QJsonValue& val : produse) {
                    QJsonObject p = val.toObject();

                    QString linie = QString("%1 - %2 RON | %3 | %4")
                                        .arg(p["nume"].toString())
                                        .arg(p["pret"].toDouble(), 0, 'f', 2)
                                        .arg(p["categorie"].toString())
                                        .arg(p["stare"].toString());

                    QListWidgetItem* item = new QListWidgetItem(linie);
                    item->setData(Qt::UserRole,     p["id_produs"].toInt());
                    item->setData(Qt::UserRole + 1, p["id_favorit"].toInt());
                    ui->FavoritesListWidget->addItem(item);
                }

                ui->FavoritesListWidget->setStyleSheet(
                    "QListWidget { background-color: white; color: #2F3640;"
                    "border: 2px solid #DCDDE1; border-radius: 10px; padding: 5px; font-size: 10pt; }"
                    "QListWidget::item { padding: 8px; border-bottom: 1px solid #DCDDE1; }"
                    "QListWidget::item:selected { background-color: #6C63FF; color: white; border-radius: 6px; }"
                    );
            });

    connect(&ServerManager::get_instance(), &ServerManager::cumparaProdusResult,
            this, [this](bool success, QString msg) {
                if (success) {
                    QMessageBox::information(this, "Succes", "✔ Produs cumpărat cu succes!");
                    cautaProduse();
                    ServerManager::get_instance().getFavorite(idUtilizatorLogat);
                    ServerManager::get_instance().getProduseUtilizator(idUtilizatorLogat);
                } else {
                    QMessageBox::warning(this, "Eroare", "✘ " + msg);
                }
            });

    initNotificari();

    connect(&ServerManager::get_instance(), &ServerManager::notificareNoua,
            this, [this](QString tip, QString mesaj) {
                // Salvează notificarea în listă
                listaNotificari.prepend("🔔 " + mesaj);
                // Reîncarcă favoritele
                ServerManager::get_instance().getFavorite(idUtilizatorLogat);
            });

    // Rezultat notificări
    connect(&ServerManager::get_instance(), &ServerManager::getNotificariResult,
            this, [this](bool success, QJsonArray notificari) {
                listaNotificari.clear();
                if (!success) return;

                int necitite = 0;
                for (const QJsonValue& val : notificari) {
                    QJsonObject n = val.toObject();
                    QString prefix = n["citita"].toInt() == 0 ? "🔔 " : "✔ ";
                    listaNotificari.append(prefix + n["mesaj"].toString());
                    if (n["citita"].toInt() == 0) necitite++;
                }

                // Afișează badge pe buton dacă are necitite
                if (necitite > 0)
                    ui->NotificariButton->setText("🔔 Notificări (" + QString::number(necitite) + ")");
                else
                    ui->NotificariButton->setText("Notificări");
            });

    // Notificare în timp real
    connect(&ServerManager::get_instance(), &ServerManager::notificareNoua,
            this, [this](QString tip, QString mesaj) {
                listaNotificari.prepend("🔔 " + mesaj);
                ServerManager::get_instance().getFavorite(idUtilizatorLogat);
                ServerManager::get_instance().getNotificari(idUtilizatorLogat);
            });

    connect(&ServerManager::get_instance(), &ServerManager::produseCumparateResult,
            this, [this](bool success, QString msg, QJsonArray produse) {
                ui->ProduseCumparateListWidget->clear();
                idComandaSelectata = -1;

                if (!success || produse.isEmpty()) {
                    ui->ProduseCumparateListWidget->addItem("Nu ai produse cumpărate.");
                    return;
                }

                for (const QJsonValue& val : produse) {
                    QJsonObject p = val.toObject();
                    bool areReview = p["are_review"].toInt() == 1;

                    QString linie = QString("%1 - %2 RON | %3 | Vânzător: %4%5")
                                        .arg(p["nume"].toString())
                                        .arg(p["pret"].toDouble(), 0, 'f', 2)
                                        .arg(p["categorie"].toString())
                                        .arg(p["vanzator"].toString())
                                        .arg(areReview ? " ✔ Review lăsat" : "");

                    QListWidgetItem* item = new QListWidgetItem(linie);
                    item->setData(Qt::UserRole,     p["id_comanda"].toInt());
                    item->setData(Qt::UserRole + 1, areReview);
                    if (areReview)
                        item->setForeground(Qt::gray);
                    ui->ProduseCumparateListWidget->addItem(item);
                }
            });

    connect(&ServerManager::get_instance(), &ServerManager::lasaReviewResult,
            this, [this](bool success, QString msg) {
                if (success) {
                    QMessageBox::information(this, "Succes", "✔ Review adăugat cu succes!");
                    ServerManager::get_instance().getProduseCumparate(idUtilizatorLogat);
                } else {
                    QMessageBox::warning(this, "Eroare", "✘ " + msg);
                }
            });

    connect(ui->LaReviewButton, &QPushButton::clicked,
            this, &SecondChance::on_LaReviewButton_clicked);

    connect(ui->ProduseCumparateListWidget, &QListWidget::itemClicked,
            this, &SecondChance::on_ProduseCumparateListWidget_itemClicked);
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
    ServerManager::get_instance().getProduseUtilizator(idUtilizatorLogat);
}

void SecondChance::on_ToMyFavoriteProducts_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->FavoritesPage);
    ServerManager::get_instance().getFavorite(idUtilizatorLogat);
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

void SecondChance::setupAppStyle()
{
    this->setStyleSheet(
        "QMainWindow {"
        "background-color: #F5F6FA;"
        "}"
        "QLabel {"
        "color: black;"
        "font-size: 10pt;"
        "}"
        );
    // În styleAllButtons() sau direct în setupAppStyle(), adaugă:
    ui->ProductsListWidget->setStyleSheet(
        "QListWidget {"
        "background-color: white;"
        "color: #2F3640;"
        "border: 2px solid #DCDDE1;"
        "border-radius: 10px;"
        "padding: 5px;"
        "font-size: 10pt;"
        "}"
        "QListWidget::item {"
        "padding: 8px;"
        "border-bottom: 1px solid #DCDDE1;"
        "}"
        "QListWidget::item:selected {"
        "background-color: #6C63FF;"
        "color: white;"
        "border-radius: 6px;"
        "}"
        "QListWidget::item:hover {"
        "background-color: #F0EFFF;"
        "color: #2F3640;"
        "}"
        );

    styleAllButtons();
    styleAllLineEdits();
    styleImportantButtons();
}

void SecondChance::styleAllButtons()
{
    QString buttonStyle =
        "QPushButton {"
        "background-color: #6C63FF;"
        "color: white;"
        "border: none;"
        "border-radius: 12px;"
        "padding: 8px;"
        "font-size: 10pt;"
        "font-weight: bold;"
        "min-width: 120px;"
        "min-height: 30px;"
        "}"
        "QPushButton:hover {"
        "background-color: #574FD6;"
        "}";

    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();

    for (QPushButton* button : buttons)
    {
        button->setStyleSheet(buttonStyle);
        button->setCursor(Qt::PointingHandCursor);
    }
}

void SecondChance::styleAllLineEdits()
{
    QString lineEditStyle =
        "QLineEdit {"
        "background-color: white;"
        "color: #2F3640;"
        "border: 2px solid #DCDDE1;"
        "border-radius: 10px;"
        "padding: 7px;"
        "font-size: 10pt;"
        "}"
        "QLineEdit:focus {"
        "border: 2px solid #6C63FF;"
        "}";

    QList<QLineEdit*> edits = this->findChildren<QLineEdit*>();

    for (QLineEdit* edit : edits)
    {
        edit->setStyleSheet(lineEditStyle);
    }
}

void SecondChance::styleImportantButtons()
{
    if (ui->CreateProductDoneButton)
    {
        ui->CreateProductDoneButton->setStyleSheet(
            "QPushButton {"
            "background-color: #00B894;"
            "color: white;"
            "border: none;"
            "border-radius: 14px;"
            "padding: 8px 14px;"
            "font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "background-color: #019875;"
            "}"
            );
    }
}

// Funcție nouă — apelată de toate: refresh, search, filtre
void SecondChance::cautaProduse()
{
    QString text      = ui->SearchProductLineEdit->text().trimmed();
    QString categorie = categorieFiltraActiva;

    ServerManager::get_instance().getProduseClient(
        idUtilizatorLogat,
        text,
        categorie
        );
}
// Înlocuiește incarcaProduse() complet:
void SecondChance::incarcaProduse()
{
    ui->ProductsListWidget->clear();
    idProdusSelectat = -1;
    cautaProduse();   // delegăm tot la cautaProduse
}


void SecondChance::on_ProductsListWidget_itemClicked(QListWidgetItem *item)
{
    if (!item) {
        idProdusSelectat = -1;
        return;
    }
    // Luăm ID-ul real din baza de date, nu indexul din listă
    idProdusSelectat = item->data(Qt::UserRole).toInt();
    qDebug() << "Produs selectat ID:" << idProdusSelectat;
}
void SecondChance::on_BuyProductButton_clicked()
{
    if (idProdusSelectat <= 0) {
        QMessageBox::warning(this, "Eroare", "Selectează un produs!");
        return;
    }

    // Confirmare înainte de cumpărare
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirmare",
        "Ești sigur că vrei să cumperi acest produs?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply != QMessageBox::Yes) return;

    ServerManager::get_instance().cumparaProdus(idUtilizatorLogat, idProdusSelectat);
}

void SecondChance::on_ViewProductDetailsButton_clicked()
{
    QListWidgetItem *item = ui->ProductsListWidget->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Eroare", "Selectează un produs!");
        return;
    }

    QString text      = item->text();
    QString pozaCale  = item->data(Qt::UserRole + 1).toString();
    QString descriere = item->data(Qt::UserRole + 2).toString();
    int idVanzator    = item->data(Qt::UserRole + 4).toInt();

    qDebug() << "[DEBUG] idVanzator pentru detalii =" << idVanzator;

    ServerManager::get_instance().getNotaVanzator(idVanzator);

    QMetaObject::Connection* conn = new QMetaObject::Connection();
    *conn = connect(&ServerManager::get_instance(), &ServerManager::notaVanzatorResult,
                    this, [this, text, pozaCale, descriere, conn](double nota, int nrReviewuri) {

                        disconnect(*conn);
                        delete conn;

                        qDebug() << "[DEBUG] nota =" << nota << "nrReviewuri =" << nrReviewuri;

                        QString mesaj = "Detalii produs:\n\n" + text;

                        if (!descriere.isEmpty())
                            mesaj += "\n\nDescriere: " + descriere;

                        QString stele = "";
                        int stelaInt = qRound(nota);
                        for (int i = 1; i <= 5; i++)
                            stele += (i <= stelaInt) ? "★" : "☆";

                        if (nrReviewuri == 0)
                            mesaj += "\n\n⭐ Vânzător fără review-uri încă.";
                        else
                            mesaj += QString("\n\n%1 %2/5 (%3 review-uri)")
                                         .arg(stele).arg(nota, 0, 'f', 1).arg(nrReviewuri);

                        QMessageBox msgBox(this);
                        msgBox.setWindowTitle("Detalii produs");

                        if (!pozaCale.isEmpty()) {
                            QPixmap pix(pozaCale);
                            if (!pix.isNull())
                                msgBox.setIconPixmap(pix.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                            else
                                mesaj += "\n\n⚠ Imaginea nu poate fi încărcată.";
                        } else {
                            mesaj += "\n\n📷 Fără poză.";
                        }

                        msgBox.setText(mesaj);
                        msgBox.exec();
                    });
}

void SecondChance::on_AddToFavoritesButton_clicked()
{
    if (idProdusSelectat <= 0) {
        QMessageBox::warning(this, "Eroare", "Selectează un produs!");
        return;
    }
    ServerManager::get_instance().adaugaFavorit(idUtilizatorLogat, idProdusSelectat);
}
void SecondChance::actualizeazaListaFavorite()
{
    qDebug() << "Lista favorite actualizată:" << favorite;
}

void SecondChance::on_SearchProductButton_clicked()
{
        cautaProduse();
}

void SecondChance::on_ClearSearchButton_clicked()
{
    ui->SearchProductLineEdit->clear();

    for (int i = 0; i < ui->ProductsListWidget->count(); i++)
    {
        ui->ProductsListWidget->item(i)->setHidden(false);
    }
}

void SecondChance::on_RefreshProductsButton_clicked()
{
    cautaProduse();
}

void SecondChance::initNotificari()
{
    // Panou notificări în colțul din dreapta jos
    notificariWidget = new QListWidget(this);
    notificariWidget->setFixedSize(300, 200);
    notificariWidget->hide();
    notificariWidget->setStyleSheet(
        "QListWidget {"
        "background-color: white;"
        "border: 2px solid #6C63FF;"
        "border-radius: 10px;"
        "padding: 5px;"
        "font-size: 9pt;"
        "}"
        "QListWidget::item {"
        "padding: 6px;"
        "border-bottom: 1px solid #DCDDE1;"
        "color: #2F3640;"
        "}"
        );
}

void SecondChance::adaugaNotificare(const QString& mesaj)
{
    if (!notificariWidget) return;

    // Poziționează în colțul din dreapta jos
    int x = this->width()  - notificariWidget->width()  - 10;
    int y = this->height() - notificariWidget->height() - 10;
    notificariWidget->move(x, y);
    notificariWidget->raise();
    notificariWidget->show();

    QListWidgetItem* item = new QListWidgetItem("🔔 " + mesaj);
    item->setForeground(QColor("#6C63FF"));
    notificariWidget->insertItem(0, item);  // adaugă la început

    nrNotificariNecitite++;

    // Ascunde automat după 5 secunde
    QTimer::singleShot(5000, this, [this]() {
        notificariWidget->hide();
    });
}

void SecondChance::on_NotificariButton_clicked()
{
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Notificări");
    dialog->setMinimumSize(400, 300);
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QListWidget* lista = new QListWidget(dialog);
    lista->setStyleSheet(
        "QListWidget { background-color: white; color: #2F3640;"
        "border: 2px solid #DCDDE1; border-radius: 10px; padding: 5px; font-size: 10pt; }"
        "QListWidget::item { padding: 8px; border-bottom: 1px solid #DCDDE1; }"
        "QListWidget::item[citita='0'] { font-weight: bold; color: #6C63FF; }"
        );

    if (listaNotificari.isEmpty()) {
        lista->addItem("Nu ai notificări.");
    } else {
        for (const QString& notif : listaNotificari)
            lista->addItem(notif);
    }

    QPushButton* stergeBtn = new QPushButton("Marchează toate ca citite", dialog);
    stergeBtn->setStyleSheet(
        "QPushButton { background-color: #00B894; color: white; border-radius: 10px;"
        "padding: 8px; font-weight: bold; }"
        "QPushButton:hover { background-color: #019875; }"
        );
    connect(stergeBtn, &QPushButton::clicked, this, [this, dialog]() {
        ServerManager::get_instance().marcheazaCitite(idUtilizatorLogat);
        ui->NotificariButton->setText("Notificări");
        dialog->close();
        // Reîncarcă notificările
        ServerManager::get_instance().getNotificari(idUtilizatorLogat);
    });

    QPushButton* closeBtn = new QPushButton("Închide", dialog);
    closeBtn->setStyleSheet(
        "QPushButton { background-color: #6C63FF; color: white; border-radius: 10px;"
        "padding: 8px; font-weight: bold; }"
        "QPushButton:hover { background-color: #574FD6; }"
        );
    connect(closeBtn, &QPushButton::clicked, dialog, &QDialog::close);

    layout->addWidget(lista);
    layout->addWidget(stergeBtn);
    layout->addWidget(closeBtn);

    dialog->setLayout(layout);
    dialog->exec();
}

void SecondChance::on_LogOutButton_clicked()
{
    // Reset state intern
    idUtilizatorLogat = 0;
    idProdusSelectat  = -1;
    listaNotificari.clear();
    categorieFiltraActiva = "";

    // Curăță listele
    ui->ProductsListWidget->clear();
    ui->FavoritesListWidget->clear();
    ui->SearchProductLineEdit->clear();
    ui->checkBox_Incaltaminte->setChecked(false);
    ui->checkBox_Imbracaminte->setChecked(false);
    ui->NotificariButton->setText("Notificări");

    // Navighează la pagina de login
    ui->ProductDetailPage->setCurrentWidget(ui->ChooseAccountTypePage);
}


void SecondChance::on_BackToSettingsProduseCumparate_clicked()
{
        ui->ProductDetailPage->setCurrentWidget(ui->SettingsClient);
}


void SecondChance::on_ProduseCumparate_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->ProduseCumparatePage);
    ServerManager::get_instance().getProduseCumparate(idUtilizatorLogat);
}
void SecondChance::on_ToProduseCumparateButton_clicked()
{
    ui->ProductDetailPage->setCurrentWidget(ui->ProduseCumparatePage);
    ServerManager::get_instance().getProduseCumparate(idUtilizatorLogat);
}

void SecondChance::on_ProduseCumparateListWidget_itemClicked(QListWidgetItem* item)
{
    qDebug() << "[DEBUG] item clicked in ProduseCumparate";
    if (!item) return;
    idComandaSelectata = item->data(Qt::UserRole).toInt();
    qDebug() << "[DEBUG] idComandaSelectata setat la:" << idComandaSelectata;
}

void SecondChance::on_LaReviewButton_clicked()
{
    qDebug() << "[DEBUG] LaReview apasat, idComandaSelectata =" << idComandaSelectata;

    if (idComandaSelectata <= 0) {
        QMessageBox::warning(this, "Eroare", "Selectează un produs!");
        return;
    }

    QListWidgetItem* item = ui->ProduseCumparateListWidget->currentItem();
    if (item && item->data(Qt::UserRole + 1).toBool()) {
        QMessageBox::warning(this, "Eroare", "Ai lăsat deja un review pentru acest produs!");
        return;
    }

    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Lasă un review");
    dialog->setMinimumWidth(350);
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QLabel* labelNota = new QLabel("Selectează nota (1-5 stele):", dialog);
    labelNota->setStyleSheet("font-weight: bold; color: #2F3640; font-size: 11pt;");
    layout->addWidget(labelNota);

    QHBoxLayout* stelaLayout = new QHBoxLayout();
    QButtonGroup* group = new QButtonGroup(dialog);
    for (int i = 1; i <= 5; i++) {
        QPushButton* stea = new QPushButton(QString("★ %1").arg(i), dialog);
        stea->setCheckable(true);
        stea->setStyleSheet(
            "QPushButton { background-color: #DCDDE1; color: #2F3640; border-radius: 8px;"
            "padding: 10px; font-size: 14pt; }"
            "QPushButton:checked { background-color: #F9CA24; color: white; }"
            );
        group->addButton(stea, i);
        stelaLayout->addWidget(stea);
    }
    layout->addLayout(stelaLayout);

    QPushButton* trimiteBtn = new QPushButton("Trimite review", dialog);
    trimiteBtn->setStyleSheet(
        "QPushButton { background-color: #00B894; color: white; border-radius: 10px;"
        "padding: 8px; font-weight: bold; margin-top: 10px; }"
        "QPushButton:hover { background-color: #019875; }"
        );
    connect(trimiteBtn, &QPushButton::clicked, this, [this, dialog, group]() {
        int nota = group->checkedId();
        if (nota < 1 || nota > 5) {
            QMessageBox::warning(dialog, "Eroare", "Selectează o notă!");
            return;
        }
        ServerManager::get_instance().lasaReview(
            idUtilizatorLogat,
            idComandaSelectata,
            nota,
            ""  // fara comentariu
            );
        dialog->close();
    });

    QPushButton* closeBtn = new QPushButton("Anulează", dialog);
    closeBtn->setStyleSheet(
        "QPushButton { background-color: #6C63FF; color: white; border-radius: 10px;"
        "padding: 8px; font-weight: bold; }"
        "QPushButton:hover { background-color: #574FD6; }"
        );
    connect(closeBtn, &QPushButton::clicked, dialog, &QDialog::close);

    layout->addWidget(trimiteBtn);
    layout->addWidget(closeBtn);

    dialog->setLayout(layout);
    dialog->exec();
}
