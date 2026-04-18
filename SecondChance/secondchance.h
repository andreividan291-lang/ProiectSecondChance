    #ifndef SECONDCHANCE_H
    #define SECONDCHANCE_H
    #include <QMainWindow>
    #include <QLineEdit>
    #include <QPushButton>
    #include <QDebug>
    #include <QRegularExpression>
    #include <QFileDialog>
    #include <QTimer>
    #include <QDir>
    #include "servermanager.h"

    QT_BEGIN_NAMESPACE
    namespace Ui { class SecondChance; }
    QT_END_NAMESPACE

    class SecondChance : public QMainWindow
    {
        Q_OBJECT
    public:
        SecondChance(QWidget *parent = nullptr);
        ~SecondChance();

    private slots:
        // Navigare
        void on_SignInButton_clicked();
        void on_SignUpButton_clicked();
        void on_SignInClientButton_clicked();
        void on_SignUpClientButton_clicked();
        void on_ChooseClientTypeButton_clicked();
        void on_BackButtonSU_clicked();
        void on_BackButtonSI_clicked();
        void on_ChooseAdminClientButton_clicked();
        void on_AdminSignInButton_clicked();
        void on_BackToUserType_clicked();
        void on_BackButtonSI_Admin_clicked();
        void on_FromAdminSignInToAccountType_clicked();
        void on_Create_Product_clicked();
        void on_pushButton_clicked();

        // Actiuni Logica
        void on_SignIntoAppButton_clicked();
        void on_SignUpIntoApp_clicked();
        void on_SignIntoAppButton_Admin_clicked();
        void on_CreateProductDoneButton_clicked();
        void on_FillWalletDoneButton_clicked();
        void on_ChangeEmailDoneButton_clicked();
        void on_ChangePasswordDoneButton_clicked();

        // Focus / Return Pressed
        void onEmailReturnPressed();
        void onParolaReturnPressed();
        void onNumeReturnPressed();
        void onPrenumeReturnPressed();
        void onNrTelefonReturnPressed();
        void onBioReturnPressed();
        void onSignInEmailReturnPressed();
        void onSignInPasswordPressed() { signInParolaEdit->clearFocus(); }
        void onEmailAdminReturnPressed();
        void onParolaAdminEmailPressed();
        void onCodPersonalEmailPressed();
        void onCreateProductTitleReturnPressed();
        void onCreateProductDescriptionReturnPressed();
        void onCreateProductPriceReturnPressed();
        void onCreateProductCategoryReturnPressed();
        void onCreateProductLocationReturnPressed();
        void onCreateProductConditionReturnPressed();
        void insertNewSumOfMoneyPressed();

        void on_ToSettingsPushButton_clicked();

        void on_ToMyProductsPushButton_clicked();

        void on_ToMyFavoriteProducts_clicked();

        void on_ToMyAccountPushButton_clicked();


        void on_ToChangeMailPagePushButton_clicked();

        void on_ToChangePasswordPagePushButton_clicked();

        void on_FromFillWalletToSettingsBackButton_clicked();

        void on_FromFavoritesToSettingsBackButton_clicked();

        void on_FromMyProductsToSettingsBackButton_clicked();

        void on_FromSettingsToSettingsBackButton_clicked();

        void on_FillWalletPushButton_clicked();

        void on_FromChangePasswordBackButton_clicked();

        void on_FromChangeEmailBackButton_clicked();

        void on_FromCreateProductBackButton_clicked();

        void on_FromMyAccountBackButton_clicked();

        void on_ChoosePicturePushButton_clicked();

    private:
        Ui::SecondChance *ui;

        // Pointeri UI - Sign Up
        QLineEdit *emailLineEdit, *parolaLineEdit, *numeLineEdit, *prenumeLineEdit;
        QLineEdit *nrTelefonLineEdit, *bioLineEdit;

        // Pointeri UI - Sign In
        QLineEdit *signInEmailEdit, *signInParolaEdit;

        // Pointeri UI - Admin
        QLineEdit *emailLineEdit_admin, *parolaLineEdit_admin, *codPersonalEdit_admin;

        // Pointeri UI - Produs
        QLineEdit *createProductTitleLineEdit, *createProductDescriptionLineEdit;
        QLineEdit *createProductPriceLineEdit, *createProductCategoryLineEdit;
        QLineEdit *createProductLocationLineEdit, *createProductConditionLineEdit;
        QLineEdit *insertNewSumOfMoney;
        QLineEdit *insertNewMailLine;
        QLineEdit *insertNewPasswordLine;
        //de programat ca mai sus QLine ul numit InsertNewPasswordLine
        //de programat ca mai sus QLine ul numit InsertNewMailLine
        //de programat ca mai sus QLine ul numit InsertNewSumOfMoneyLine
        //de facut logica in VS, de adaugat in baza de date, la creeare de cont campul "Portofel" care la creearea contului e 0;
        //de rezolvat cu produsele, nu merge
        //de curatat codul

        // State intern
        QString calePozaSelectata = "";
        int     idUtilizatorLogat = 0;

        // Helper-e de validare vizuala
        void setFieldError(QLineEdit* field, const QString& tooltip = "");
        void setFieldOk(QLineEdit* field);
        void clearFieldState(QLineEdit* field);
        bool validateSignUpFields();
        bool validateSignInFields();
        bool validateAdminFields();
        bool validateProductFields();
        void connectClearOnType(QLineEdit* field);
    };

    #endif // SECONDCHANCE_H
