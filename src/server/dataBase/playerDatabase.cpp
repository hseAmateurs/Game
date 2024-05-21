#include "playerDatabase.h"

// Функция для загрузки данных из файла
void PlayerDatabase::loadDatabase() {
    players.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return; // Or throw an exception
    }
    std::string line;
    while (getline(file, line)) {
        //std::cout << "Read line: " << line << std::endl;
        std::stringstream ss(line);
        Player player;
        ss >> player.login >> player.password >> player.deaths >> player.kills >> player.game_counter;
        std::string friend_login;
        while (ss >> friend_login) {
            player.friends.push_back(friend_login);
        }
        players.push_back(player);
    }
    file.close();

}

// Функция для сохранения данных в файл
void PlayerDatabase::saveDatabase() {
    std::ofstream file(filename);
    for (const Player& player : players) {
        file << player.login << " " << player.password << " "
             << player.deaths << " " << player.kills << " "
             << player.game_counter;
        for (const std::string& friend_login : player.friends) {
            file << " " << friend_login;
        }
        file << std::endl;
    }
    file.close();
}

// Функция для добавления нового игрока
void PlayerDatabase::addPlayer(std::string login, std::string password) {
    loadDatabase();
    Player newPlayer = {login, password, 0, 0, 0, {}};
    players.push_back(newPlayer);
    saveDatabase(); // Сохраняем изменения
}

// Функция для поиска игрока по логину
int PlayerDatabase::findLogin(const std::string login) {
    loadDatabase();
    int i = 0;
    for (Player& player : players) {
        if (player.login == login) {
            return i;
        }
        i++;
    }
    return -1;
}

int PlayerDatabase::findUser(const std::string login, const std::string password){
    int loginCode = findLogin(login);
    if (loginCode == -1)
        return -1;
    else{
        if (players[loginCode].password == password)
            return 0;
        else
            return 1;
    }
}

// Функция для обновления статистики игрока
void PlayerDatabase::updateStats(const std::string login, int new_deaths, int new_kills) {
    int userId = findLogin(login);

    players[userId].deaths += new_deaths;
    players[userId].kills += new_kills;
    players[userId].game_counter++;

    saveDatabase(); // Сохраняем изменения
}

// Функция для добавления друга
void PlayerDatabase::addFriend(const std::string login, const std::string& friend_login) {
    int userId = findLogin(login);
    players[userId].friends.push_back(friend_login);
    saveDatabase(); // Сохраняем изменения
}

std::vector<std::string> PlayerDatabase::getFriends(const std::string login) {
    int userId = findLogin(login);
    return players[userId].friends;// Возвращает пустой вектор, если игрок не найден
}

// Функция для получения статистики игрока
std::tuple<int, int, int> PlayerDatabase::getStats(const std::string& login) {
    int userId = findLogin(login);
    return std::make_tuple(players[userId].deaths, players[userId].kills, players[userId].game_counter);
}