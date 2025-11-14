import platform
import random
import time
import datetime
import matplotlib.pyplot as plt

def zapisz_wykres(test_results, filename="wykres_sortowania.png"):
    sizes = list(test_results.keys())
    times = list(test_results.values())

    plt.figure(figsize=(8, 5))
    plt.plot(sizes, times, marker='o', linestyle='-', color='blue')
    plt.title("Czas sortowania vs rozmiar tablicy")
    plt.xlabel("Rozmiar tablicy")
    plt.ylabel("Czas (s)")
    plt.grid(True)
    plt.savefig(filename)
    plt.close()

def mierzczas():
    sizes = [1000, 10000, 100000]
    results = {}

    for size in sizes:
        arr = [random.randint(0, 1000 ** 6) for _ in range(size)]

        start = time.time()
        sorted_arr = sorted(arr)
        end = time.time()

        results[size] = end - start

    return results


def generuj_raport(test_results):
    filename = f"raport_testu_{datetime.date.today()}.md"

    with open(filename, "w", encoding="utf-8") as f:

        f.write("# Raport testów wydajnosci\n\n")

        f.write("## Data:\n")
        f.write(f"{datetime.datetime.now()}\n\n")

        f.write("Porownanie czasu sortowania tablic rożnych rozmiarow.\n\n")

        f.write("## Srodowisko:\n")
        f.write(f"- System: {platform.system()} {platform.release()}\n")
        f.write(f"- Procesor: {platform.processor()}\n")
        f.write(f"- Python: {platform.python_version()}\n\n")

        f.write("## Wyniki testow:\n")
        f.write("Rozmiar tablicy | Czas (s)\n")
        f.write("---|---\n")
        for size, czas in test_results.items():
            f.write(f"{size} | {czas:.6f}\n")
        f.write("\n## Wykres\n")
        f.write("![Wykres sortowania](wykres_sortowania.png)\n")

results = mierzczas()
zapisz_wykres(results)
generuj_raport(results)
print(f"Raport zapisano do pliku")