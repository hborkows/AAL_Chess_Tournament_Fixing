# AAL_Chess_Tournament_Fixing
Projekt na uczelnię z przedmiotu Analiza Algorytmów.

# Autor: Hubert Borkowski 283668
# Zadanie: Ustawianie turnieju szachowego, aby wygrał konkretny zawodnik

# Specyfikacja problemu
Zadanie polega na ustawieniu drzewka turnieju szachowego tak,
aby przy znanych z góry wynikach wszystkich możliwych partii,
wygrał wybrany przez nas zawodnik.
Liczba zawodników jest równa 2^n.

# Tryby wykonania
1. Tryb testowy ręczny
    Użytkownik ręcznie wprowadza dane wejściowe
    Sluży do ręcznego testowania poprawności
2. Tryb automatyczny
    Automatycznie generowana jest instancja problemu o zadanej wielkości
    Możliwe wylosowanie wygrywającego zawodnika
3. Tryb automatyczny z pomiarem czasu wykonania
    Automatyczne generowane są instancje problemu od wielkości 1 do zadanej maksymalnej wielkości
    Dla każdej instancji problemu wygrywający zawodnik jest losowany
    Słuzy do pomiaru efektywności algorytmu

# Metody rozwiązania
1. Algorytm brute-force przeszukujący w pesymistycznym przypadku całą przestrzeń możliwych rozwiązań
2. Algorytm brute-force z punktu 1. wsparty sortowaniem graczy według ilości wygranych przez nich partii

# Zastosowane struktury danych
1. Wektor Graczy, przy czym każdy Gracz ma wektor oponentów, z którymi wygrywa i wektor oponentów, z którymi przegrywa
2. Drzewo, w którym zapisywane jest rozwiązanie. Każdy węzeł drzewa reprezentuje rozgrywaną partię w turnieju.
    Węzeł przechowuje informację o 2 Graczach w danej partii.

# Pliki źródłowe
1. main.cpp - główna funkcja programu, wywołania odpowiednich funkcji z innych klas
2. Interface.h i Interface.cpp - zawiera klasę Interface, która wywołuje metody klasy wykonującej algorytm (GameTree) i wyśiwietlająca wyniki
2. GameTree.h i GameTree.cpp - zawiera klasę GameTree, która zajmuje się przechowywaniem wektora Graczy i obsługą algorytmów rozwiązujących problem
3. Player.h i Player,cpp - zawiera klasę Player, która jest reprezentacją pojedynczego Gracza
4. DataGenerator.h i DataGenerator.cpp - zawiera klasę DataGenerator, która zajmuje się generowaniem danych dla klasy GameTree


