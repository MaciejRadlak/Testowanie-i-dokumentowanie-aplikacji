| Parametr | Opis |
| :--- | :--- |
| **Temat** | **Automatyzacja przetwarzania wyników testów wydajnościowych i wizualizacja danych (Python)** |
| **Wykonawcy** | **Maciej Radlak, Adrian Markowski** |
| **Data** | **28.11.2025** |
| **Klasa** | **4D (technik programista)** |
| **Poziom** | **Podstawowy** |

---

## 1. Cel ćwiczenia

1.  Opracowanie skryptu automatyzującego proces ekstrakcji danych (ETL) z surowych logów tekstowych do ustrukturyzowanego formatu CSV.
2.  Praktyczne zastosowanie wyrażeń regularnych (moduł `re`) do identyfikacji i pobierania zmiennych (tryb sortowania, wielkość danych N, czas operacji) z niejednorodnych ciągów znaków.
3.  Wykorzystanie bibliotek analitycznych środowiska Python (`pandas`, `matplotlib`) do wizualizacji wyników badań wydajnościowych.
4.  Analiza charakterystyki czasowej badanego algorytmu w zależności od wielkości zbioru danych wejściowych.

## 2. Narzędzia i środowisko

* **Język programowania:** Python 3.x
* **Środowisko programistyczne (IDE):** Visual Studio Code / PyCharm
* **Biblioteki standardowe:** `re` (obsługa wyrażeń regularnych), `csv` (obsługa plików tekstowych rozdzielanych znakiem).
* **Biblioteki zewnętrzne:** `pandas` (analiza i przetwarzanie danych), `matplotlib` (generowanie wykresów).
* **Dane wejściowe:** Plik `wyniki.txt` zawierający logi z aplikacji testującej (format: `Czas sortowania (...) : ... s`).

## 3. Przebieg ćwiczenia

### Etap 1: Parsowanie danych surowych (`main.py`)
W pierwszej fazie zaimplementowano skrypt odpowiedzialny za odczyt danych z pliku tekstowego. Wobec niestandardowego formatu logów zastosowano wzorzec Regex:
`r"Czas sortowania \((?P<tryb>indeksy|wskazniki)\)(?:\s*\[N=(?P<N>\d+)\])?\s*:\s*(?P<czas>\d+(?:\.\d+)?)\s*s"`

Skrypt realizuje następujące zadania:
1.  Iteracyjny odczyt pliku `wyniki.txt`.
2.  Dopasowanie wzorca do każdej linii i pominięcie błędnych rekordów (np. "Error Test").
3.  Ekstrakcja grup nazwanych (`tryb`, `N`, `czas`) i konwersja czasu na milisekundy.
4.  Zapis sformatowanych danych do pliku `wyniki.csv`.

### Etap 2: Analiza i wizualizacja (`panda.py`)
W drugiej fazie wykorzystano bibliotekę `pandas` do wczytania przetworzonych danych. Przeprowadzono czyszczenie danych wejściowych (konwersja separatora dziesiętnego z przecinka na kropkę, usunięcie jednostek tekstowych). Następnie wygenerowano wykres liniowy obrazujący trend wzrostu czasu wykonywania algorytmu.

## 4. Wyniki

### A. Zestawienie tabelaryczne
W wyniku działania skryptu `main.py` uzyskano plik CSV. Poniższa tabela przedstawia fragment przetworzonych danych:

| tryb | N | czas_s | czas_ms |
| :--- | :--- | :--- | :--- |
| indeksy | 100 | 0.012 | 12.0 |
| wskazniki | 200 | 0.018 | 18.0 |
| indeksy | 300 | 0.025 | 25.0 |
| wskazniki | 400 | 0.031 | 31.0 |
| indeksy | 500 | 0.044 | 44.0 |
| wskazniki | 600 | 0.051 | 51.0 |
| indeksy | 700 | 0.062 | 62.0 |
| wskazniki | 800 | 0.073 | 73.0 |
| indeksy | 900 | 0.084 | 84.0 |
| wskazniki | 1000 | 0.095 | 95.0 |

### B. Wizualizacja graficzna
Na podstawie zebranych danych wygenerowano wykres (`Wykres panda.png`), obrazujący zależność czasu sortowania od liczby elementów w tablicy.

![Wykres zależności czasu od wielkości danych](Wykres%20panda.png)

Wykres wskazuje na liniową zależność czasu wykonywania operacji od wielkości danych wejściowych (N). Brak gwałtownych skoków (tzw. *spikes*) sugeruje stabilną pracę algorytmu w badanym zakresie.

## 5. Wnioski końcowe

1.  **Efektywność automatyzacji:** Wykorzystanie skryptów Python pozwoliło na szybkie przetworzenie setek linii logów, eliminując ryzyko błędu ludzkiego przy ręcznym przepisywaniu danych.
2.  **Zastosowanie Regex:** Wyrażenia regularne okazały się kluczowe dla precyzyjnej filtracji danych, umożliwiając oddzielenie poprawnych wyników od komunikatów błędów systemowych (np. błędów alokacji).
3.  **Biblioteka Pandas:** Użycie `pandas` znacząco uprościło proces normalizacji danych (typowanie zmiennych, operacje na stringach) w porównaniu do standardowych operacji na listach.
4.  **Charakterystyka algorytmu:** Analiza wykresu potwierdza, że czas wykonania rośnie proporcjonalnie do liczby elementów `N`. Jest to zachowanie oczekiwane i pożądane dla stabilnych algorytmów sortowania.
5.  **Skalowalność rozwiązania:** Opracowane rozwiązanie jest uniwersalne – zmiana formatu logów wymaga jedynie aktualizacji wzorca Regex, bez konieczności przebudowy całego algorytmu analizy.

---

## Załącznik – przykładowe fragmenty kodu
**Listing 1. Logika parsująca z użyciem Regex (`main.py`)**

```python
pattern = re.compile(
    r"Czas sortowania \((?P<tryb>indeksy|wskazniki)\)"
    r"(?:\s*\[N=(?P<N>\d+)\])?"
    r"\s*:\s*(?P<czas>\d+(?:\.\d+)?)\s*s"
)

rows = []

with open("wyniki.txt", "r", encoding="utf-8") as f:
    for line in f:
        m = pattern.search(line)
        if m:
            d = m.groupdict()
            czas_s = float(d.get("czas"))
            rows.append({
                "tryb": d.get("tryb"),
                "N": d.get("N"),
                "czas_s": czas_s,
                "czas_ms": czas_s * 1000
            })

```

**Listing 2. Przygotowanie danych i generowanie wykresu (`panda.py`))**
```
# bezpieczne wczytanie CSV
df = pd.read_csv("wyniki.csv", sep=';', encoding="utf-8-sig")

# przygotowanie kolumny czas_s
df["czas_s"] = (
    df["czas_s"]
    .astype(str)
    .str.replace(",", ".", regex=False)
    .str.replace(" s", "", regex=False)
    .str.strip()
    .astype(float)
)

# wykres
plt.figure()
plt.plot(df.index, df["czas_s"], marker='o')
plt.title("Czas sortowania (sekundy)")
plt.xlabel("Pomiar")
plt.ylabel("Czas [s]")
plt.grid(True)
plt.show()
```