#include "puzzle.h"

int puzzle::getSize()
{
    return fl_size;
}

int puzzle::getEmpty()
{
    return empty_place;
}

vector<int> puzzle::getState()
{
    return fl;
}

void puzzle::setState(vector<int> state)
{
    fl = state;
    for (int i = 0; i < fl_size*fl_size; i++)
        if (!(fl[i]))
            empty_place = i;
}

puzzle::puzzle(int size) {
    fl_size = (int)sqrt(size);
    fl.resize(size);
    for (int i = 0; i < size - 1; i++) {
        fl[i] = i + 1;
    }
    fl[size - 1] = 0;
    empty_place = size - 1;
}

void puzzle::move(int c_i, int c_j) {
    int turn = (c_i - 1) * fl_size - 1 + c_j, i = 0;
    int diff = (c_i - 1) * fl_size  - 1 + c_j - empty_place;
    if (empty_place / fl_size + 1 == turn / fl_size + 1) {
        for (i = empty_place; i != turn; i += diff / abs(diff)) {
            fl[i] = fl[i + (diff / abs(diff))];
            fl[i + 1 * (diff / abs(diff))] = 0;
        }
        empty_place = i;
        Game_status = 1;
    }
    if (!(abs(diff) % fl_size)) {
        for (i = empty_place; i != turn; i += diff / abs(diff) * fl_size) {
            fl[i] = fl[i + (diff / abs(diff) * fl_size)];
            fl[i + (diff / abs(diff) * fl_size)] = 0;
        }
        empty_place = i;
        Game_status = 1;
    }

}

vector<int> puzzle::move(vector<int> fl_c, int diff) {
    int zero_place = 0;
    for (int i = 0; i < fl_size*fl_size; i++)
        if (!(fl_c[i]))
            zero_place = i;
    int turn = diff + zero_place;
    if (turn  > fl_size*fl_size - 1 || turn  < 0)
        return fl_c;
    if (zero_place / fl_size  == turn / fl_size || zero_place % fl_size == turn % fl_size) {
        fl_c[zero_place] = fl_c[turn];
        fl_c[turn] = 0;
    }
    return fl_c;
}

int puzzle::status() {
    if (Game_status) {
        for (int i = 0; i < fl_size*fl_size - 1; i++) {
            if (fl[i] != i + 1)
                return 1;
        }
        return 0;
    }
    return 1;

}

int puzzle::isGame() {
    int inv = 0;
    for (int i = 0; i < fl_size*fl_size - 1; i++)
        if(fl[i])
            for (int j = i + 1; j < fl_size*fl_size; j++)
                if (fl[j])
                    if (fl[i] > fl[j])
                        inv++;
    return (inv + (empty_place / fl_size + 1) * ((fl_size + 1) % 2)) % 2;

}

void puzzle::shuffle(){
    srand(time(NULL));
    do {
        for (int i = fl_size * fl_size - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(fl[j], fl[i]);
            if (!(fl[i]))
                empty_place = i;
            if (!(fl[j]))
                empty_place = j;
        }
    } while (isGame());


}

int puzzle::heuristic(vector<int> state) {
    int distance = 0;
    for (int i = 0; i < fl_size * fl_size; i++) {
        if (!(state[i]))
            continue;
        distance += abs((state[i] - 1) / fl_size - i / fl_size) +
                abs((state[i] - 1) % fl_size - i % fl_size);
    }
    return distance;
}

vector<vector<int>> puzzle::solve() {
    vector<int> goal(fl_size*fl_size);
    for (int i = 0; i < fl_size * fl_size - 1; i++)
        goal[i] = i + 1;
    goal[fl_size * fl_size - 1] = 0;
    pair<int, vector<int>> element;
    priority_queue <pair<int, vector<int>>, vector<pair<int, vector<int>>> , greater<pair<int, vector<int>>>> q;
    q.emplace(heuristic(fl),fl);
    map<vector<int>, vector<int>> path;
    map<vector<int>, bool> used;
    used[fl] = true;
    vector<int> current;
    while (!(q.empty())) {
        current = q.top().second;
        q.pop();
        if (current == goal)
            break;
        vector<int> next;
        next = move(current, 1);
        if (!(used[next])) {
            q.emplace(heuristic(next),next);
            path[next] = current;
            used[next] = true;
        }
        next = move(current, -1);
        if (!(used[next])) {
            q.emplace(heuristic(next), next);
            path[next] = current;
            used[next] = true;
        }
        next = move(current, fl_size);
        if (!(used[next])) {
            q.emplace(heuristic(next), next);
            path[next] = current;
            used[next] = true;
        }
        next = move(current, -fl_size);
        if (!(used[next])) {
            q.emplace(heuristic(next), next);
            path[next] = current;
            used[next] = true;
        }
    }
    vector<vector<int>> a;
    a.push_back(current);
    while (current != fl) {
        current = path[current];
        a.push_back(current);
    }
    reverse(a.begin(), a.end());
    return a;
}
