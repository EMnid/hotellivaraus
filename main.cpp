#include <iostream>
#include <vector>
#include <limits>
#include <random>
#include <iomanip>


using namespace std;
// Aliohjelma valinnaisen yksittäisen huoneen varaamiseksi
bool varaaYksiHuone(vector<bool> &varatutHuoneet, double hintaPerYo)
{
    // Huoneen valinta arvotulta väliltä, syötteentarkistus
    int huoneenNumero;
    cout << "Anna huoneen numero (1..." << varatutHuoneet.size() << "): ";
    while (!(cin >> huoneenNumero) || huoneenNumero < 1 || huoneenNumero > varatutHuoneet.size())
    {
        cout << "Virheellinen syote. Anna kelvollinen huoneen numero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // Suoritetaan arvonta
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, varatutHuoneet.size());

    int arvottuHuoneenNumero;
    do
    {
        arvottuHuoneenNumero = distribution(gen);
    } while (varatutHuoneet[arvottuHuoneenNumero - 1]);

    if (varatutHuoneet[huoneenNumero - 1])
    {
        cout << "Huone on jo varattu. Valitse toinen huone." << endl;
        return false; // Palautetaan false, koska varaaminen epäonnistui
    }
    else
    { // Varaaminen onnistui, syöte öiden määrälle ja virheentarkistus
        varatutHuoneet[huoneenNumero - 1] = true;
        cout << "Huone numero " << huoneenNumero << " varattu onnistuneesti." << endl;
        int paivienMaara;
        cout << "Anna oiden määrä: ";
        while (!(cin >> paivienMaara) || paivienMaara <= 0)
        {
            cout << "Virheellinen syote. Anna kelvollinen oiden maara: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        double loppusumma = paivienMaara * hintaPerYo;
        cout << "Laskun loppusumma: " << loppusumma << " euroa." << endl;
        return true; // Palautetaan true, kun varaaminen onnistui
    }
}

// Aliohjelma laskemaan vapaat huoneet
void laskeVapaatHuoneet(const vector<bool> &varatutHuoneet, int &vapaatHuoneet)
{
    for (bool varattu : varatutHuoneet)
    {
        if (!varattu)
        {
            vapaatHuoneet++;
        }
    }
}

// Aliohjelma palauttamaan ohjelma alkuvalikkoon huoneiden ollessa täynnä
void varaaHuoneet(vector<bool> &varatutHuoneet, double hintaPerYo)
{
    int vapaatHuoneet = 0;
    laskeVapaatHuoneet(varatutHuoneet, vapaatHuoneet);

    if (vapaatHuoneet == 0)
    {
        cout << "Kaikki huoneet ovat varattuja." << endl;
        return;
    }

    if (varaaYksiHuone(varatutHuoneet, hintaPerYo))
    {
        return;
    }
}

// Aliohjelma satunnaisen huoneen varaamiseksi
void arvoHuone(vector<bool> &varatutHuoneet, double hintaPerYo)
{
    int vapaatHuoneet = 0;
    laskeVapaatHuoneet(varatutHuoneet, vapaatHuoneet);

    if (vapaatHuoneet == 0)
    {
        cout << "Kaikki huoneet ovat varattuja." << endl;
        return;
    }
    // Suoritetaan arvonta
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, varatutHuoneet.size());

    int arvottuHuoneenNumero;
    do
    {
        arvottuHuoneenNumero = distribution(gen);
    } while (varatutHuoneet[arvottuHuoneenNumero - 1]);

    varatutHuoneet[arvottuHuoneenNumero - 1] = true;
    cout << "Satunnainen huone numero " << arvottuHuoneenNumero << " varattu onnistuneesti." << endl;
    // Öiden määrän syötteentarkistus
    int paivienMaara;
    cout << "Anna oiden maara: ";
    while (!(cin >> paivienMaara) || paivienMaara <= 0)
    {
        cout << "Virheellinen syote. Anna kelvollinen oiden maara: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // Lasketaan loppusumma
    double loppusumma = paivienMaara * hintaPerYo;
    cout << "Laskun loppusumma: " << loppusumma << " euroa." << endl;
}

int main()
{
    // Alustetaan satunnaislukugeneraattori
    std::random_device rd;
    std::mt19937 gen(rd());

    // Aliohjelma luo satunnaisen määrän huoneita ja asettaa satunnaisen hinnan yöltä
    std::uniform_int_distribution<int> roomCountDistribution(30, 70); // 30-70 huonetta
    std::uniform_real_distribution<double> priceDistribution(80.0, 100.0); // 80-100 euroa yöltä

    int huoneidenMaara = roomCountDistribution(gen);
    double hintaPerYo = priceDistribution(gen);
    cout << fixed << setprecision(2);
    cout << "Hotellissa on " << huoneidenMaara << " huonetta." << endl;
    cout << "Huoneen hinta yolta on " << hintaPerYo << " euroa." << endl;

    vector<bool> varatutHuoneet(huoneidenMaara, false);
    // Aloitusvalikko virhesyötteen tarkastuksen kanssa
    int valinta;
    do
    {
        cout << "\nValitse toiminto:\n1. Varaa huone\n2. Arvo huone satunnaisesti\n3. Lopeta\n";
        while (!(cin >> valinta) || valinta < 1 || valinta > 3)
        {
            cout << "Virheellinen syote. Anna kelvollinen valinta: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        // Aloitusvalikosta aliohjelmiin siirto tai lopetus
        switch (valinta)
        {
        case 1:
            varaaHuoneet(varatutHuoneet, hintaPerYo);
            break;

        case 2:
            arvoHuone(varatutHuoneet, hintaPerYo);
            break;
        case 3:
            cout << "Kiitos ohjelman kaytosta. Nakemiin!" << endl;
            break;
        }

    } while (valinta != 3);

    return 0;
}
