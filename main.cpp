#include <iostream>
#include "data_structure.h"

using namespace std;

int main()
{
    // Declarations & Notifications
    map<int, struct edge_struct> edges_map;
    map<int, struct edge_endpoint> vertices_map;
    map<int, VNC> vnc_map;
    vector<int> sorted_vertices;

    Graph my_graph;
    cout << "A new Graph object created !" << endl;
    VNC my_vnc;
    cout << "A new VNC object created !" << endl;

    // Mass loading
    infra_and_requests_mass_loading(edges_map,vertices_map,my_graph,vnc_map);

    // Getting the graph recap
    my_graph.get_graph_recap();

    // Checking all the possible paths
    my_graph.check_all_possible_paths();

    // Sorting all the vertices, using the the cpu and ram values
    sorted_vertices = sort_vertices_by_resources(vertices_map);
    cout << "\t====>Result(Descending regarding cpu and ram) : ";
    for (vector<int>::iterator it(sorted_vertices.begin()); it<sorted_vertices.end(); ++it)
    {
        cout << to_string(*it) + " ";
    }

    cout << "\n\nVNC placement trial...\n" << requests_placement_process(my_graph,vertices_map,vnc_map) << endl;

    return 0;
}
