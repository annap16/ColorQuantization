
# Choose your language version
- [Polski](#color-quant-pol)
- [English](#color-quant-en)

---

# Kwantyzacja palety kolorów <a name="color-quant-pol"></a>
![Screenshot](https://private-user-images.githubusercontent.com/160714456/413885750-748ad039-76ee-4d26-b12f-44d23585fc64.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3Mzk4MDA1NDgsIm5iZiI6MTczOTgwMDI0OCwicGF0aCI6Ii8xNjA3MTQ0NTYvNDEzODg1NzUwLTc0OGFkMDM5LTc2ZWUtNGQyNi1iMTJmLTQ0ZDIzNTg1ZmM2NC5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMjE3JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDIxN1QxMzUwNDhaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT0yZDkxOGU0OTY4NDU5MmEyZDQ4Y2QzY2E1NGIzZmIzNzA1NGFmNWRkYjA2ZGU1MWU3NWRiZjM3YTQzOTFmOTg0JlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.wpqGYdbCY97RMOWZebtbNSWWpYBt7145XDIaZ_CF_2o)

Repozytorium zawiera projekt implementujący algorytmy ditheringu dla obrazów. Celem projektu jest stworzenie algorytmów: algorytmu popularnościowego oraz algorytmów drżenia (ordered dithering random/relative, error diffusion dithering, average dithering),
który jest powszechnie stosowany w grafice komputerowej do rozdzielania obrazów na ograniczoną liczbę kolorów. Projekt pozwala na konwersję obrazów zawierających pełną paletę kolorów do obrazów o mniejszej liczbie kolorów, zachowując jak największą jakość wizualną, 
w zależności od wybranego algorytmu konwersji.

## Opis Projektu
1. **Wczytywanie obrazu:** aplikacja umożliwia załadowanie obrazu wejściowego do programu.
2. **Zapisanie przetworzonego obrazu:** po zastosowaniu algorytmu ditheringu, użytkownik może zapisać obraz z ograniczoną paletą kolorów.
3. **Wybór algorytmu kwantyzacji:** Użytkownik ma możliwość wyboru jednego z dostępnych algorytmów ditheringu oraz dostosowania parametrów algorytmu.
4. **Generowanie domyślnego obrazu:** Aplikacja umożliwia wygenerowanie obrazu specjalnej szachownicy, która służy do łatwego porównania wyników różnych algorytmów. W centrum szachownicy znajduje się kwadrat wypełniony pełną paletą kolorów.

## Zastosowane algorytmy
### 1. **Average Dithering**
Average Dithering jest prostą metodą, w której dla każdego piksela obrazu obliczana jest średnia wartość koloru z kilku najbliższych pikseli. Na podstawie tej średniej przypisywany jest odpowiedni kolor z ograniczonej palety. 

### 2. **Error Diffusion Dithering**
Error Diffusion Dithering jest algorytmem, w którym błąd koloru piksela jest "rozpraszany" do sąsiednich pikseli w obrazie.
Algorytm wykorzystuje tzw. "błąd" (różnicę między wartością rzeczywistą a przypisaną wartością koloru) i przekazuje ten błąd do sąsiednich pikseli, co pozwala uzyskać bardziej naturalny efekt.

### 3. **Ordered Dithering (Random i Relative)**
Ordered Dithering to technika ditheringu, która używa ustalonego wzorca, by przydzielić odpowiedni kolor do pikseli obrazu w celu uzyskania efektu "mniejszej liczby kolorów". Algorytm wykorzystuje tzw. matrycę wzorców, która jest powtarzana na całym obrazie.

- **Wersja losowa**: Pozycje we wzorze `n x n` są wybierane losowo:
    - `i = Random(0..n-1), j = Random(0..n-1)`
- **Wersja zależna od pozycji**: Pozycja we wzorze `n x n` zależy od pozycji piksela w obrazie:
    - `i = x % n, j = y % n` (gdzie x, y to współrzędne piksela w obrazie)

### 4. Algorytm Popularnościowy
Działa na zasadzie przypisania każdemu pikselowi obrazu jednego z wybranych kolorów, bazując na popularności (częstotliwości występowania) kolorów w obrazie. Wybór liczby kolorów do redukcji obrazu oraz samych kolorów można ustawić jako K.

# Color Palette Quantization <a name="color-quant-en"></a>
![Screenshot](https://private-user-images.githubusercontent.com/160714456/413885750-748ad039-76ee-4d26-b12f-44d23585fc64.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3Mzk4MDA1NDgsIm5iZiI6MTczOTgwMDI0OCwicGF0aCI6Ii8xNjA3MTQ0NTYvNDEzODg1NzUwLTc0OGFkMDM5LTc2ZWUtNGQyNi1iMTJmLTQ0ZDIzNTg1ZmM2NC5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMjE3JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDIxN1QxMzUwNDhaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT0yZDkxOGU0OTY4NDU5MmEyZDQ4Y2QzY2E1NGIzZmIzNzA1NGFmNWRkYjA2ZGU1MWU3NWRiZjM3YTQzOTFmOTg0JlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.wpqGYdbCY97RMOWZebtbNSWWpYBt7145XDIaZ_CF_2o)

This repository contains a project implementing dithering algorithms for images. The goal of the project is to create algorithms: the popularity algorithm and dithering algorithms (ordered dithering random/relative, error diffusion dithering, average dithering), which are widely used in computer graphics to reduce images to a limited number of colors. 
The project allows the conversion of images containing a full color palette into images with fewer colors, while preserving as much visual quality as possible, depending on the selected conversion algorithm.

## Project Description
1. **Image Loading:** The application allows the user to load an input image into the program.
2. **Saving the Processed Image:** After applying the dithering algorithm, the user can save the image with a reduced color palette.
3. **Choosing the Quantization Algorithm:** The user can choose from the available dithering algorithms and adjust the algorithm's parameters.
4. **Generating a Default Image:** The application can generate a special checkerboard image, which serves as a comparison tool for the results of different algorithms. The center of the checkerboard contains a square filled with a full color palette.

## Algorithms Used
### 1. **Average Dithering**
Average Dithering is a simple method where for each pixel in the image, the average color value of the nearest surrounding pixels is calculated. Based on this average, an appropriate color from the limited palette is assigned to the pixel.

### 2. **Error Diffusion Dithering**
Error Diffusion Dithering is an algorithm in which the color error of a pixel is "diffused" to neighboring pixels in the image. The algorithm uses the "error" (the difference between the actual value and the assigned color value) and propagates it to neighboring pixels, resulting in a more natural effect.

### 3. **Ordered Dithering (Random and Relative)**
Ordered Dithering is a dithering technique that uses a predetermined pattern to assign appropriate colors to the image pixels in order to create the effect of a "reduced color palette." The algorithm uses a so-called pattern matrix, which is repeated throughout the image.

- **Random Version:** The positions in the `n x n` pattern are chosen randomly:
    - `i = Random(0..n-1), j = Random(0..n-1)`
- **Position-dependent Version:** The position in the `n x n` pattern depends on the pixel's position in the image:
    - `i = x % n, j = y % n` (where x, y are the pixel coordinates in the image)

### 4. **Popularity Algorithm**
The Popularity Algorithm works by assigning each pixel of the image one of the selected colors based on the frequency (popularity) of colors in the image. The number of colors to reduce the image to, as well as the specific colors, can be set as `K`.

