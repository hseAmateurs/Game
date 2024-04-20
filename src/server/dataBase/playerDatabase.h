#ifndef GAME_PLAYERDATABASE_H
#define GAME_PLAYERDATABASE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>



struct Player {
    std::string login;
    std::string password;
    int deaths;
    int kills;
    int game_counter;
    std::vector<std::string> friends;
};


class PlayerDatabase{
public:
    PlayerDatabase(std::string file): filename(file) { loadDatabase(); };


//    static PlayerDatabase &instance(){
//        PlayerDatabase database;
//        return database;
//    }

    void addPlayer(std::string login, std::string password);
    int findLogin(const std::string login); // при существоании возвращает позицию в БД, иначе -1
    int findUser(const std::string login, const std::string password); // при совпадении возвращает 0, при неправильном пароле возвращает 1б при отсутствии логина -1
    void updateStats(std::string login, int new_deaths, int new_kills);
    void addFriend(const std::string login, const std::string& friend_login);
    std::vector<std::string> getFriends(const std::string login);
    std::tuple<int, int, int> getStats(const std::string& login);

private:
    std::vector<Player> players;
    std::string filename;

    void loadDatabase();
    void saveDatabase();
};








#endif //GAME_PLAYERDATABASE_H
