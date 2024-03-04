#include <iostream>
#include <fstream>
#include <vector>
#include <random>

const int Pmin = 2;
using namespace std;

int main()
{
    ifstream input_file("tist.txt");           // Fichier d'entrée contenant l'instance de group-shop
    ofstream output_file("tist.txt"); // Fichier de sortie pour la nouvelle instance

    if (!input_file)
    {
        cerr << "Erreur: Impossible d'ouvrir le fichier d'entrée." << endl;
        return 1;
    }

    if (!output_file)
    {
        cerr << "Erreur: Impossible de créer le fichier de sortie." << endl;
        return 1;
    }

    int num_jobs, num_machines;
    input_file >> num_jobs >> num_machines;

    output_file << num_jobs << " " << num_machines << endl;

    // Initialisation du générateur aléatoire
    random_device rd;
    mt19937 gen(rd());
    // uniform_int_distribution<int> sub_operation_power(Pmin, Pmax);

    for (int i = 0; i < num_jobs; ++i)
    {
        int num_groups;
        input_file >> num_groups;

        output_file << num_groups << " ";

        for (int j = 0; j < num_groups; ++j)
        {
            int num_operations;
            input_file >> num_operations;
            output_file << num_operations << " ";

            for (int k = 0; k < num_operations; ++k)
            {
                int machine, duration;
                input_file >> machine >> duration;

                int num_subs;
                if (duration <= 4)
                {
                    uniform_int_distribution<int> num_sub_operations(2, duration);
                    num_subs = num_sub_operations(gen);
                }
                else
                {
                    uniform_int_distribution<int> num_sub_operations(2, 5);
                    num_subs = num_sub_operations(gen);
                }

                output_file << machine << " " << num_subs << " ";
                uniform_int_distribution<int> sub_operation_power(Pmin, duration);
                // Génération aléatoire des sous-opérations
                int remaining_duration = duration;
                for (int l = 0; l < num_subs - 1; ++l)
                {
                    uniform_int_distribution<int> sub_operation_duration(1, remaining_duration - (num_subs - l - 1));
                    int sub_duration = sub_operation_duration(gen);
                    remaining_duration -= sub_duration;
                    int sub_power = sub_operation_power(gen);
                    output_file << sub_duration << " " << sub_power << " ";
                }
                output_file << remaining_duration << " " << sub_operation_power(gen) << " "; // Dernière sous-opération avec la durée restante
            }
        }
        output_file << endl;
    }

    cout << "Nouvelle instance generee avec succes." << endl;

    input_file.close();
    output_file.close();

    return 0;
}
