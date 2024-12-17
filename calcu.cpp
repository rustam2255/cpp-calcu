#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QString>
#include <QLabel>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();

private:
    QLineEdit *display;
    QString currentInput;
    QString lastOperation;
    double lastValue;

    void calculateResult();
};

Calculator::Calculator(QWidget *parent) : QWidget(parent), lastValue(0.0), lastOperation("") {
    setWindowTitle("Kalkulyator");

    // Ekran qismi
    display = new QLineEdit();
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setStyleSheet("font-size: 24px; padding: 10px;");

    // Tugmalarni yaratish
    QGridLayout *gridLayout = new QGridLayout();
    QString buttons[4][4] = {
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", "C", "=", "+"}
    };

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            QPushButton *button = new QPushButton(buttons[i][j]);
            button->setStyleSheet("font-size: 18px; padding: 10px;");
            gridLayout->addWidget(button, i, j);
            connect(button, &QPushButton::clicked, this, &Calculator::onButtonClicked);
        }
    }

    // Barcha layoutlar
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(display);
    mainLayout->addLayout(gridLayout);
    setLayout(mainLayout);
}

void Calculator::onButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QString buttonText = button->text();

    if (buttonText == "C") {
        currentInput = "";
        lastOperation = "";
        lastValue = 0.0;
        display->setText("0");
    } else if (buttonText == "=") {
        calculateResult();
    } else if (buttonText == "+" || buttonText == "-" || buttonText == "*" || buttonText == "/") {
        if (!currentInput.isEmpty()) {
            lastValue = currentInput.toDouble();
            currentInput = "";
        }
        lastOperation = buttonText;
    } else {
        currentInput += buttonText;
        display->setText(currentInput);
    }
}

void Calculator::calculateResult() {
    double result = lastValue;

    if (!currentInput.isEmpty()) {
        double currentValue = currentInput.toDouble();
        if (lastOperation == "+") result += currentValue;
        else if (lastOperation == "-") result -= currentValue;
        else if (lastOperation == "*") result *= currentValue;
        else if (lastOperation == "/") result /= currentValue;

        display->setText(QString::number(result));
        currentInput = "";
        lastOperation = "";
        lastValue = result;
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Calculator calc;
    calc.resize(300, 400);
    calc.show();
    return app.exec();
}

#include "main.moc"