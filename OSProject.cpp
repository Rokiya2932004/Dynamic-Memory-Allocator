#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
#include <set>
using namespace std;
using ll = long long;

struct Process
{
    int id{}, space{};

    Process(int _id, int _space) : id(_id), space(_space) {}
};

struct Partition
{
    int id{}, space{}, allocated{};
    set<int> processes;

    Partition() {};

    Partition(int _id, int _space) : id(_id), space(_space) {}
};

// First-fit
void firstFit_allocate(Process process, vector<Partition> &partitions)
{
    for (int i = 0; i < partitions.size(); i++)
    {
        int availableSpace = partitions[i].space - partitions[i].allocated;
        if (availableSpace >= process.space)
        {
            partitions[i].allocated += process.space;
            partitions[i].processes.insert(process.id);
            return;
        }
    }
}

void firstFit_deallocate(int process_id, vector<Process> &all_processes,vector<Partition> &partitions)
{
    for (int i = 0; i < partitions.size(); i++)
    {
        if (partitions[i].processes.count(process_id) == 1)
        {
            for (int j = 0; j < all_processes.size(); j++)
            {
                if (all_processes[j].id == process_id)
                {
                    partitions[i].allocated -= all_processes[j].space;
                }
            }
            partitions[i].processes.erase(process_id);
            return;
        }
    }
}

// Best-fit
void bestFit_allocate(Process process, vector<Partition> &partitions)
{
    int best_space = INT_MAX, best_idx = -1;
    for (int i = 0; i < partitions.size(); i++)
    {
        int availableSpace = partitions[i].space - partitions[i].allocated;
        if (availableSpace >= process.space && availableSpace < best_space)
        {
            best_space = availableSpace;
            best_idx = i;
        }
    }
    if (best_idx != -1)
    {
        partitions[best_idx].allocated += process.space;
        partitions[best_idx].processes.insert(process.id);
    }
}

void bestFit_deallocate(int process_id, vector<Process> &all_processes,vector<Partition> &partitions)
{
    for (int i = 0; i < partitions.size(); i++)
    {
        if (partitions[i].processes.count(process_id) == 1)
        {
            for (int j = 0; j < all_processes.size(); j++)
            {
                if (all_processes[j].id == process_id)
                {
                    partitions[i].allocated -= all_processes[j].space;
                }
            }
            partitions[i].processes.erase(process_id);
            return;
        }
    }
}

// Worst-fit
void worstFit_allocate(Process process, vector<Partition> &partitions)
{
    int worst_space = 0, worst_idx = -1;
    for (int i = 0; i < partitions.size(); i++)
    {
        int availableSpace = partitions[i].space - partitions[i].allocated;
        if (availableSpace >= process.space && availableSpace > worst_space)
        {
            worst_space = availableSpace;
            worst_idx = i;
        }
    }
    if (worst_idx != -1)
    {
        partitions[worst_idx].allocated += process.space;
        partitions[worst_idx].processes.insert(process.id);
    }
}

void worstFit_deallocate(int process_id, vector<Process> &all_processes,
                         vector<Partition> &partitions)
{
    for (int i = 0; i < partitions.size(); i++)
    {
        if (partitions[i].processes.count(process_id) == 1)
        {
            for (int j = 0; j < all_processes.size(); j++)
            {
                if (all_processes[j].id == process_id)
                {
                    partitions[i].allocated -= all_processes[j].space;
                }
            }
            partitions[i].processes.erase(process_id);
            return;
        }
    }
}

void play(vector<Partition> &partitions)
{
    cout << "#ID ------ #Space ------ #allocated ------ #unallocated ------ #Running_processes\n";
    for (auto partition : partitions)
    {
        cout << " " << partition.id << "     |       " << partition.space << "   |   " << partition.allocated << "       |       " << partition.space - partition.allocated
             << "       |       " << "[";
        for (auto id : partition.processes)
            cout << id << ',';
        cout << "]\n";
    }
    cout << "----------------------------------------------------------------------------------------\n";
}

int main()
{
    int num_partitions;
    vector<Process> all_processes;
    cout << " # Enter Number of partitions: ";
    cin >> num_partitions;
    vector<Partition> partitions(num_partitions);
    for (int i = 0; i < num_partitions; i++)
    {
        cout << "\n  - Enter space for partition " << i+1 << " : ";
        cin >> partitions[i].space;
        partitions[i].id = i;
    }
    cout << "\n";
    cout << "=======================================\n";

    cout << "  ### Enter technique you need  ### \n";
    cout << "  ### 1. Worst Fit \n";
    cout << "  ### 2. Best Fit \n";
    cout << "  ### 3. First Fit \n";
    cout << "  ### Your choice => ";
    int choice;
    cin >> choice;
    cout << '\n';
    if (choice == 1)
    {
        int x;
        cout << " Enter command \'0\' to exit\nchoose 1 for allocate\n      2 for deallocate";
        while (cin >> x, x)
        {
            // cout << " Enter command \'0\' to exit\nchoose 1 for allocate\n       2 for deallocate";
            if (x == 1)
            {
                int process_id, space;
                cout << " Enter process id: ";
                cin >> process_id;
                cout << " Enter process space : ";
                cin >> space;
                all_processes.push_back(Process(process_id, space));
                worstFit_allocate(Process(process_id, space), partitions);
            }
            else if (x == 2)
            {
                int process_id;
                cout << " Enter process id: ";
                cin >> process_id;
                worstFit_deallocate(process_id, all_processes, partitions);
            }
            else
            {
                cout << "Invalid command, :< i will close their app.";
                exit(0);
            }
            play(partitions);
        }
    }
    else if (choice == 2)
    {
        cout << " Enter command \'0\' to exit\nchoose 1 for allocate\n       2 for deallocate";
        int x;
        while (cin >> x, x)
        {
            cout << " Enter command \'0\' to exit\nchoose 1 for allocate\n       2 for deallocate";

            if (x == 1)
            {
                int process_id, space;
                cout << " Enter process id: ";
                cin >> process_id;
                cout << " Enter process space : ";
                cin >> space;
                all_processes.push_back(Process(process_id, space));
                bestFit_allocate(Process(process_id, space), partitions);
            }
            else if (x == 2)
            {
                int process_id;
                cout << " Enter process id: ";
                cin >> process_id;
                bestFit_deallocate(process_id, all_processes, partitions);
            }
            else
            {
                cout << "Invalid command, :< i will close their app.";
                exit(0);
            }
            play(partitions);
        }
    }
    else if (choice == 3)
    {
        cout << " Enter command \'0\' to exit\nchoose 1 for allocate\n       2 for deallocate";
        int x;
        while (cin >> x, x)
        {
            cout << " Enter command \'0\' to exit\nchoose 1 for allocate\n       2 for deallocate";

            if (x == 1)
            {
                int process_id, space;
                cout << " Enter process id: ";
                cin >> process_id;
                cout << " Enter process space : ";
                cin >> space;
                all_processes.push_back(Process(process_id, space));
                firstFit_allocate(Process(process_id, space), partitions);
            }
            else if (x == 2)
            {
                int process_id;
                cout << " Enter process id: ";
                cin >> process_id;
                firstFit_deallocate(process_id, all_processes, partitions);
            }
            else
            {
                cout << "Invalid command, :< i will close their app.";
                exit(0);
            }
            play(partitions);
        }
    }
    else
    {
        cout << "\n Invalid Choice\n";
    }
    return 0;
}
