#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void sum_average(vector<vector<int>> &task_times, vector<int> &ws, vector<int> &tasktype, int receive_timee, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        if (tasktype[i] == 1)
        {
            ws[i] = receive_timee;
        }
        else
        {
            int sum = 0;
            for (int j = 0; j < m; j++)
            {
                sum += task_times[i][j];
            }
            ws[i] = sum / m;
        }
    }
}
void assignment(vector<vector<int>> &task_times, vector<int> &tasktype, int receive_timee, int n, int m)
{
    int mini[n];
    for (int i = 0; i < n; i++)
    {
        mini[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mini[i] > task_times[i][j])
            {
                mini[i] = task_times[i][j];
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (mini[i] > receive_timee)
        {
            tasktype[i] = 1;
        }
        else
            tasktype[i] = 0;
    }
}
int helper_function_one(vector<vector<int>> &task_times, vector<int> &priorities, vector<vector<int>> &successors, vector<int> &tasktype, vector<int> &ready_timenergy_consumption_localocal, vector<int> &ready_timenergy_consumption_cloudloud, vector<int> &ready_time_ws, vector<int> &finish_time_ws, vector<int> &finish_time_wr, vector<int> &finish_timenergy_consumption_localocal, vector<int> &finish_time, vector<int> &core, vector<int> &cores, int n, int m, int offloading_time, int receive_time, int cloud_time, vector<vector<int>> list)
{
    int first = priorities[n - 1];
    ready_timenergy_consumption_localocal[first] = 0;
    ready_time_ws[first] = 0;
    finish_time_ws[first] = ready_time_ws[first] + offloading_time;
    ready_timenergy_consumption_cloudloud[first] = finish_time_ws[first];

    return first;
}

void helper_function_two(int first, vector<int> &ready_timenergy_consumption_cloudloud, int receive_time, int cloud_time, vector<int> &finish_time_wr, vector<int> &finish_timenergy_consumption_localocal, vector<int> &finish_time, vector<int> &core, vector<vector<int>> list, vector<int> &cores)
{
    finish_time_wr[first] = ready_timenergy_consumption_cloudloud[first] + cloud_time + receive_time;
    finish_time[first] = finish_time_wr[first];
    finish_timenergy_consumption_localocal[first] = 0;
    cores[first] = 3;
    list[0].push_back(first);
    core[3] = finish_time[first];
}

void helper_function_three(int first, int index, vector<int> &finish_time, vector<int> &finish_time_wr, vector<int> &core, vector<vector<int>> list, vector<int> &cores, vector<int> &finish_timenergy_consumption_localocal, vector<int> &finish_time_ws)
{
    cores[first] = index;
    list[index + 1].push_back(first);
    core[3] = finish_time_ws[first];
    finish_time_wr[first] = 0;
    finish_time[first] = finish_timenergy_consumption_localocal[first];
}

void helper_function_four(int first, int index, vector<int> &finish_time, vector<int> &finish_time_wr, vector<int> &core, vector<vector<int>> list, vector<int> &cores, vector<int> &finish_timenergy_consumption_localocal)
{
    finish_time[first] = finish_time_wr[first];
    finish_timenergy_consumption_localocal[first] = 0;
    core[index] = finish_time[first];
    list[0].push_back(first);
    cores[first] = 3;
}

void calculate_priorities(vector<vector<int>> &task_times, vector<int> &priority, vector<int> &priorities, vector<vector<int>> &successors, vector<int> &ws, vector<int> &tasktype, int receive_timee, int n, int m)
{
    sum_average(task_times, ws, tasktype, receive_timee, n, m);
    priority[n - 1] = ws[n - 1];
    for (int i = n - 1; i >= 0; i--)
    {
        int maxi = 0;
        for (int j = n - 1; j >= 0; j--)
        {
            if (successors[i][j] == 1 && priority[j] > maxi)
            {
                maxi = priority[j];
            }
        }
        priority[i] = ws[i] + maxi;
    }
    vector<pair<int, int>> vect;
    for (int i = 0; i < n; i++)
    {
        vect.push_back(make_pair(priority[i], i));
    }
    sort(vect.begin(), vect.end());
    for (int i = 0; i < n; i++)
    {
        priorities[i] = vect[i].second;
    }
}

void helper_function_five(int i, int index, vector<int> &finish_time, vector<int> &finish_time_wr, vector<int> &core, vector<vector<int>> list, vector<int> &cores, vector<int> &finish_timenergy_consumption_localocal)
{
    finish_time[i] = finish_timenergy_consumption_localocal[i];
    finish_time_wr[i] = 0;
    core[index] = finish_time[i];
    list[index + 1].push_back(i);
    cores[i] = index;
}

void helper_function_six(int i, vector<int> &finish_time, vector<int> &finish_time_wr, vector<int> &core, vector<vector<int>> list, vector<int> &cores, vector<int> &finish_timenergy_consumption_localocal)
{
    finish_time[i] = finish_time_wr[i];
    finish_timenergy_consumption_localocal[i] = 0;
    core[3] = finish_time[i];
    list[0].push_back(i);
    cores[i] = 3;
}

void helper_function_seven(int i, vector<int> &finish_time, vector<int> &finish_time_wr, vector<int> &core, vector<vector<int>> list, vector<int> &cores, vector<int> &finish_timenergy_consumption_localocal,
                           vector<int> &ready_timenergy_consumption_cloudloud, int receive_time, int cloud_time, vector<int> &finish_time_ws)
{
    cores[i] = 3;
    list[0].push_back(i);
    core[3] = finish_time_ws[i];
    finish_timenergy_consumption_localocal[i] = 0;
    finish_time_wr[i] = ready_timenergy_consumption_cloudloud[i] + cloud_time + receive_time;
    finish_time[i] = finish_time_wr[i];
}

int find_maximum(int a, int b)
{
    return max(a, b);
}

void execution(vector<vector<int>> &task_times, vector<int> &priorities, vector<vector<int>> &successors, vector<int> &tasktype, vector<int> &ready_timenergy_consumption_localocal, vector<int> &ready_timenergy_consumption_cloudloud, vector<int> &ready_time_ws, vector<int> &finish_time_ws, vector<int> &finish_time_wr, vector<int> &finish_timenergy_consumption_localocal, vector<int> &finish_time, vector<int> &core, vector<int> &cores, int n, int m, int offloading_time, int receive_time, int cloud_time, vector<vector<int>> list)
{

    int first = helper_function_one(task_times, priorities, successors, tasktype, ready_timenergy_consumption_localocal, ready_timenergy_consumption_cloudloud, ready_time_ws, finish_time_ws, finish_time_wr, finish_timenergy_consumption_localocal, finish_time, core, cores, n, m, offloading_time, receive_time, cloud_time, list);
    if (tasktype[first] == 1)
    {
        helper_function_two(first, ready_timenergy_consumption_cloudloud, receive_time, cloud_time, finish_time_wr, finish_timenergy_consumption_localocal, finish_time, core, list, cores);
    }
    else
    {
        int mini = INT_MAX;
        int index;
        for (int i = 0; i < m; i++)
        {
            if (task_times[first][i] < mini)
            {
                mini = task_times[first][i];
                index = i;
            }
        }
        finish_timenergy_consumption_localocal[first] = ready_timenergy_consumption_localocal[first] + mini;
        finish_time_wr[first] = ready_timenergy_consumption_cloudloud[first] + cloud_time + receive_time;
        finish_timenergy_consumption_localocal[first] <= finish_time_wr[first] ? helper_function_three(first, index, finish_time, finish_time_wr, core, list, cores, finish_timenergy_consumption_localocal, finish_time_ws) : helper_function_four(first, index, finish_time, finish_time_wr, core, list, cores, finish_timenergy_consumption_localocal);
    }
    int a = n - 2;
    while (a >= 0)
    {
        int i = priorities[a];
        int maxi = 0;
        int j = 0;
        while (j < n)
        {
            if (successors[j][i] == 1 && maxi < find_maximum(finish_timenergy_consumption_localocal[j], finish_time_wr[j]))
            {
                maxi = max(finish_timenergy_consumption_localocal[j], finish_time_wr[j]);
            }
            j++;
        }
        ready_timenergy_consumption_localocal[i] = maxi;
        int maxj = 0;
        j = 0;
        while (j < n)
        {
            if (successors[j][i] == 1 && maxj < find_maximum(finish_timenergy_consumption_localocal[j], finish_time_ws[j]))
            {
                maxj = max(finish_timenergy_consumption_localocal[j], finish_time_ws[j]);
            }
            j++;
        }
        ready_time_ws[i] = maxj;
        finish_time_ws[i] = max(core[3], ready_time_ws[i]) + offloading_time;
        int max_j_c = 0;
        j = 0;
        while (j < n)
        {
            if (successors[j][i] == 1 && max_j_c < finish_time_wr[j] - receive_time)
            {
                max_j_c = finish_time_wr[j] - receive_time;
            }
            j++;
        }
        ready_timenergy_consumption_cloudloud[i] = find_maximum(finish_time_ws[i], max_j_c);
        if (tasktype[i] == 1)
        {
            helper_function_seven(i, finish_time, finish_time_wr, core, list, cores, finish_timenergy_consumption_localocal, ready_timenergy_consumption_cloudloud, receive_time, cloud_time, finish_time_ws);
        }
        else
        {
            int rt, index;
            int f = INT_MAX;
            int j = 0;
            while (j < m)
            {
                rt = find_maximum(ready_timenergy_consumption_localocal[i], core[j]);
                if (f > rt + task_times[i][j])
                {
                    f = rt + task_times[i][j];
                    index = j;
                }
                j++;
            }
            ready_timenergy_consumption_localocal[i] = f - task_times[i][index];
            finish_timenergy_consumption_localocal[i] = f;
            finish_time_wr[i] = ready_timenergy_consumption_cloudloud[i] + cloud_time + receive_time;
            finish_timenergy_consumption_localocal[i] <= finish_time_wr[i] ? helper_function_five(i, index, finish_time, finish_time_wr, core, list, cores, finish_timenergy_consumption_localocal) : helper_function_six(i, finish_time, finish_time_wr, core, list, cores, finish_timenergy_consumption_localocal);
        }
        a--;
    }
}

void print(vector<vector<int>> list, vector<int> &start_time, vector<int> &end_time, int t, float e)
{
    cout << endl;
    cout << "MCC Task Scheduling" << endl;

    for (int i = 0; i < list.size(); i++)
    {
        if (i != 3)
        {
            cout << "Core " << i + 1 << ": ";
        }
        else
        {
            cout << "Cloud: ";
        }
        for (int j = 0; j < list[i].size(); j++)
        {
            cout << list[i][j] + 1 << "(" << start_time[list[i][j]] << "-" << end_time[list[i][j]] << ") ";
        }
        cout << endl;
    }
    cout << "Energy Consumption: " << e << endl;
    cout << "Finish Time: " << t << endl;
}

void mcc_algorithm(vector<vector<int>> list, vector<vector<int>> &task_times, vector<vector<int>> &successors, vector<int> &cores, int tmax, int t, float e, int n, int m, vector<int> &start_time, vector<int> &end_time, int energy_consumption_cloud, vector<vector<int>> &energy_consumption_local)
{

    int a = 0;
    int c = 0;
    while (a == 0)
    {
        float m_rat = 0;
        int n1 = 0, k1 = 0, id1 = 0, id2 = 0, t_n = t;
        float e_n = e;
        int t1 = 0, t2 = 0;
        int core_t[10], start_time1[10], fin_time[10];
        ;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m + 1; j++)
            {
                int core2[10], core3[4], rt[10], rt1[10] = {0}, finish_time[10] = {0}, finish_time1[10], pushed[10] = {0};
                vector<vector<int>> tlist(4);
                int index1, index2 = 0;
                for (int i = 0; i < 10; i++)
                {

                    core2[i] = cores[i];
                    finish_time1[i] = end_time[i];
                    rt1[i] = start_time[i];
                }
                for (int a = 0; a < list.size(); a++)
                {
                    core3[a] = 0;
                    int b = 0;
                    while (b < list[a].size())
                    {
                        tlist[a].push_back(list[a][b]);
                        b++;
                    }
                }
                int currencloud_timeore = cores[i];
                for (int a = 0; a < tlist[currencloud_timeore].size(); a++)
                {
                    if (tlist[currencloud_timeore][a] == i)
                    {
                        index1 = a;
                    }
                }
                tlist[currencloud_timeore].erase(tlist[currencloud_timeore].begin() + index1);
                int max_j = 0;
                for (int a = 0; a < n; a++)
                {
                    if (successors[a][i] == 1 && max_j < finish_time1[a])
                    {
                        max_j = finish_time1[a];
                    }
                }
                rt[i] = max_j;

                core2[i] = j;

                if (tlist[j].size() == 0)
                {
                    index2 = 0;
                }
                else if (tlist[j].size() == 1)
                {
                    index2 = rt1[tlist[j][0]] > rt[i] ? 0 : 1;
                }
                else
                {
                    if (rt1[tlist[j][0]] > rt[i])
                    {
                        index2 = 0;
                    }
                    else if (rt1[tlist[j][tlist[j].size() - 1]] <= rt[i])
                    {
                        index2 = tlist[j].size();
                    }
                    else
                    {
                        for (int b = 0; b < tlist[j].size() - 1; b++)
                        {
                            if (rt[i] >= rt1[tlist[j][b]] && rt[i] <= rt1[tlist[j][b + 1]])
                            {
                                index2 = b + 1;
                            }
                        }
                    }
                }
                tlist[j].insert(tlist[j].begin() + index2, i);

                int ready1[10], ready2[10];
                for (int a = 0; a < 10; a++)
                {
                    ready1[a] = 0;
                }
                for (int a = 0; a < 10; a++)
                {
                    for (int b = 0; b < 10; b++)
                    {
                        if (successors[a][b] == 1)
                        {
                            ready1[b] += 1;
                        }
                    }
                    ready2[a] = 1;
                }

                for (int a = 0; a < 4; a++)
                {
                    if (tlist[a].size() > 0)
                    {
                        ready2[tlist[a][0]] = 0;
                    }
                }

                stack<int> s;
                for (int a = 0; a < 10; a++)
                {
                    if (ready1[a] == 0 && ready2[a] == 0 && pushed[a] == 0)
                    {
                        s.push(a);
                        pushed[a] = 1;
                    }
                }
                int current1 = s.top();
                s.pop();
                rt[current1] = 0;
                rt[current1] = max(core3[core2[current1]], rt[current1]);
                finish_time[current1] = rt[current1];
                finish_time[current1] += core2[current1] == 3 ? 5 : task_times[current1][core2[current1]];
                core3[core2[current1]] = core2[current1] == 3 ? rt[current1] + 3 : finish_time[current1];

                for (int a = 0; a < 10; a++)
                {
                    if (successors[current1][a] == 1)
                    {
                        ready1[a] -= 1;
                    }
                }
                ready2[current1] = 1;

                if (tlist[core2[current1]].size() > 1)
                {
                    for (int a = 1; a < tlist[core2[current1]].size(); a++)
                    {
                        if (tlist[core2[current1]][a - 1] == current1)
                        {
                            ready2[tlist[core2[current1]][a]] = 0;
                        }
                    }
                }

                for (int a = 0; a < 10; a++)
                {
                    if (ready1[a] == 0 && ready2[a] == 0 && pushed[a] == 0)
                    {
                        s.push(a);
                        pushed[a] = 1;
                    }
                }

                while (s.size() != 0)
                {
                    int current = s.top();
                    s.pop();
                    int max_j = 0;
                    for (int a = 0; a < n; a++)
                    {
                        if (successors[a][current] == 1 && max_j < finish_time[a])
                        {
                            max_j = finish_time[a];
                        }
                    }
                    rt[current] = max_j;

                    rt[current] = find_maximum(core3[core2[current]], rt[current]);
                    finish_time[current] = rt[current];
                    finish_time[current] += core2[current] == 3 ? 5 : task_times[current][core2[current]];
                    core3[core2[current]] = core2[current] == 3 ? rt[current] + 3 : finish_time[current];

                    for (int a = 0; a < 10; a++)
                    {
                        if (successors[current][a] == 1)
                        {
                            ready1[a] -= 1;
                        }
                    }
                    ready2[current] = 1;
                    if (tlist[core2[current]].size() > 1)
                    {
                        for (int a = 1; a < tlist[core2[current]].size(); a++)
                        {
                            if (tlist[core2[current]][a - 1] == current)
                            {
                                ready2[tlist[core2[current]][a]] = 0;
                            }
                        }
                    }
                    for (int a = 0; a < 10; a++)
                    {
                        if (ready1[a] == 0 && ready2[a] == 0 && pushed[a] == 0)
                        {
                            s.push(a);
                            pushed[a] = 1;
                        }
                    }
                }
                int tcurr = finish_time[n - 1];
                int ecurr = 0;
                for (int a = 0; a < 10; a++)
                {
                    ecurr += core2[a] == 3 ? energy_consumption_cloud : energy_consumption_local[a][core2[a]];
                }

                if (tcurr <= t && ecurr < e_n)
                {
                    t1 = 1, n1 = i, k1 = j, id1 = index1, id2 = index2, t_n = tcurr, e_n = ecurr;
                    for (int a = 0; a < 10; a++)
                    {
                        core_t[a] = core2[a];
                        start_time1[a] = rt[a];
                        fin_time[a] = finish_time[a];
                    }
                }
                if (tcurr > t && tcurr <= tmax && t1 == 0 && ecurr < e && m_rat < double((e - ecurr) / (tcurr - t)))
                {
                    m_rat = double((e - ecurr) / (tcurr - t));
                    t2 = 1, n1 = i, k1 = j, id1 = index1, id2 = index2, t_n = tcurr, e_n = ecurr;
                    for (int a = 0; a < 10; a++)
                    {
                        core_t[a] = core2[a];
                        start_time1[a] = rt[a];
                        fin_time[a] = finish_time[a];
                    }
                }
            }
        }
        if (t1 != 1 && t2 != 1)
        {
            a = 1;
        }
        else
        {
            list[cores[n1]].erase(list[cores[n1]].begin() + id1);
            list[k1].insert(list[k1].begin() + id2, n1);
            t = t_n;
            e = e_n;
            for (int a = 0; a < 10; a++)
            {
                cores[a] = core_t[a];
                start_time[a] = start_time1[a];
                end_time[a] = fin_time[a];
            }
            c = c + 1;
        }
    }

    print(list, start_time, end_time, t, e);
}

int main()
{
    int m = 3, n = 10;
    vector<vector<int>> task_times = {{9, 7, 5},
                                      {8, 6, 5},
                                      {6, 5, 4},
                                      {7, 5, 3},
                                      {5, 4, 2},
                                      {7, 6, 4},
                                      {8, 5, 3},
                                      {6, 4, 2},
                                      {5, 3, 2},
                                      {7, 4, 2}};
    vector<vector<int>> successors = {{0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
                                      {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    vector<int> tasktype(task_times.size(), 0);
    vector<int> priority(task_times.size(), 0);
    vector<int> priorities(task_times.size(), 0);
    vector<int> ws(task_times.size(), 0);
    vector<int> core(4, 0);
    vector<int> cores(task_times.size(), 0);
    vector<int> ready_timenergy_consumption_localocal(task_times.size(), 0);
    vector<int> ready_timenergy_consumption_cloudloud(task_times.size(), 0);
    vector<int> ready_time_ws(task_times.size(), 0);
    vector<int> finish_time_ws(task_times.size(), 0);
    vector<int> finish_time_wr(task_times.size(), 0);
    vector<int> finish_timenergy_consumption_localocal(task_times.size(), 0);
    vector<int> finish_time(task_times.size(), 0);

    vector<vector<int>> list(4);
    int offloading_time = 3;
    int cloud_time = 1;
    int receive_time = 1;
    int receive_timee = offloading_time + cloud_time + receive_time;
    vector<vector<int>> energy_consumption_local(task_times.size(), vector<int>(3, 0));
    vector<int> core_energy = {1, 2, 4};
    float cloud_energy = 0.5;
    float energy_consumption_cloud = cloud_energy * offloading_time;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            energy_consumption_local[i][j] = core_energy[j] * task_times[i][j];
        }
    }

    assignment(task_times, tasktype, receive_timee, n, m);
    calculate_priorities(task_times, priority, priorities, successors, ws, tasktype, receive_timee, n, m);
    execution(task_times, priorities, successors, tasktype, ready_timenergy_consumption_localocal, ready_timenergy_consumption_cloudloud, ready_time_ws, finish_time_ws, finish_time_wr, finish_timenergy_consumption_localocal, finish_time, core, cores, n, m, offloading_time, receive_time, cloud_time, list);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (cores[j] == i)
            {
                list[i].push_back(j);
            }
        }
    }
    float e = 0;
    for (int i = 0; i < 10; i++)
    {
        if (cores[i] == 3)
        {
            e += energy_consumption_cloud;
        }
        else
        {
            e += energy_consumption_local[i][cores[i]];
        }
    }
    vector<int> start_time(task_times.size());
    for (int i = 0; i < 10; i++)
    {
        start_time[i] = max(ready_timenergy_consumption_localocal[i], ready_time_ws[i]);
    }

    int tmin = finish_time[n - 1];
    int tmax = 1.5 * tmin;
    cout << "Initial Task Scheduling " << endl;
    for (int i = 0; i < list.size(); i++)
    {
        if (i == 3)
        {
            cout << "Cloud: ";
        }
        else
        {
            cout << "Core" << i + 1 << ": ";
        }
        for (int j = 0; j < list[i].size(); j++)
        {
            cout << list[i][j] + 1 << " ";
        }
        cout << endl;
    }
    cout << "Energy Consumption: " << e << endl;
    cout << "Finish Time: " << tmin << endl;
    cout << endl;

    mcc_algorithm(list, task_times, successors, cores, tmax, tmin, e, 10, 3, start_time, finish_time, energy_consumption_cloud, energy_consumption_local);

    return 0;
}
