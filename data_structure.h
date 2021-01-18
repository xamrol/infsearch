#ifndef DATA_STRUCTURE_H_INCLUDED
#define DATA_STRUCTURE_H_INCLUDED
#include <list>
#include <vector>
#include <map>
#include <string>
//#include <memory>

/*
  All the structures designed to represent the important objects
*/
// A structure to define a vertex in the graph
struct edge_endpoint {
    int v_id;
    int available_disk_capacity;
    int available_ram;
    int available_cpu;
    int cost;
};

// A structure to define an edge in the graph
struct edge_struct {
  int e_id;
  long bandwidth;
  long residual_bandwidth;
  int delay;
  int cost;
  int source;
  int destination;
};

// A structure to create sets of edges
// A rank will be used to identify a subset's priority
struct subset {
    int parent;
    int rank;
};

// A structure to define a virtual network function
struct vnf {
    int vnf_id;
    std::string description;
    int cpu;
    int ram;
    int disk_capacity;
};

// A structure designed to represent a virtual link (between VNFs)
struct v_links {
    int v_link_id;
    std::string description;
    long requested_bandwidth;
    long requested_latency;
    struct vnf* source_vnf;
    struct vnf* destination_vnf;
};

// Two useful structures to build a custom recap for each request's placement
struct report_recap {
	int r_id;
	bool processed;
	double elapsed_time;
	std::string output;
	std::string metrics_recap;
	std::string final_path;
	std::string nodes_recap;
	std::string vnf_infos;
	std::string vlinks_infos;
	std::string placement_result;
};
struct vlink_support {
    int v_id;
    bool supported;
    std::string description;
    std::string graph_src_node;
    std::string graph_dest_node;
    std::string graph_edges;
};



/*
  A class Graph, for any object that represents a graph
*/
class Graph {
private:
    int nb_vertices;
    int nb_edges;
    std::vector<int> all_vertices;
    std::vector<int> edges_id_tab;
    std::vector<int> tmp_used_edges;
    std::map<int, struct edge_struct> edges_internal_map;
    std::map<int, struct edge_endpoint> vertices_internal_map;
    //struct subset *subsets;
    //std::unique_ptr<std::vector<struct subset>> subsets;
    std::vector<struct subset> subsets;
    std::map<int, std::vector<int>> vertex_with_parent_map;
    std::map<int, std::vector<int>> path_from_vertex_map;
    std::map<int, bool> used_nodes_map;
    std::map<int, bool> used_edges_map;

public:
    // Constructor
    Graph();

    // Modifiers
    void add_edge(struct edge_struct& newedge);
    void add_vertices_map(std::map<int, struct edge_endpoint>& vertices_internal_map_);
    void update_edge_bw_by_id(int const & i, long const & bandwidth_);
    void update_vertex_cpu_by_id(int const & i, long const & cpu_);
    void update_vertex_infos(int const & i, int const & cpu, int const & ram, int const & capacity);
    void update_used_nodes_map(int const & i);
    void update_used_edges_map(int const & i);
    void reset_tmp_used_edges();
    void update_tmp_used_edges(int const & i);

    // Accessors
    int get_nb_vertices() const;
    int get_nb_edges() const;
    struct subset get_subset(int const & i);
    std::string get_all_subsets_infos();
    std::map<int, std::vector<int>> get_path_from_vertex_map() const;
    struct edge_endpoint get_vertex_infos_by_id(int const & i);
    struct edge_endpoint* get_vertex_addr_by_id(int const & i);
    struct edge_struct* get_edge_addr_by_id(int const & i);
    std::vector<int> get_edges_id_tab() const;
    std::vector<int> get_all_vertices() const;
    unsigned int get_used_nodes_map_size() const;
    std::map<int, bool> get_used_nodes_map() const;
    unsigned int get_used_edges_map_size() const;
    std::map<int, bool> get_used_edges_map() const;
    std::vector<int> get_tmp_used_edges() const;


    // Other methods
    //int find_root(struct subset subsets[], int i);
    //void union_subsets(struct subset subsets[], int x, int y);
    int find_root(int i);
    void union_subsets(int x, int y);
    bool union_find_traversal();
    void get_graph_recap();
    void check_all_possible_paths();

};



/*
  A class VirtualNetworkChain (VNC), for the Virtual functions' chain to place
*/
class VNC {
private:
    int nb_vnf, nb_vlinks;
    std::map<int, struct vnf> vnf_internal_map;
    std::map<int, struct v_links> vlink_internal_map;
    std::map<std::string, std::string> vnc_infos_map;
    std::map<int, bool> vnf_placement_status;
    std::map<int, struct vlink_support> vlink_process_status;
    std::map<struct vnf*, std::map<struct v_links*, struct edge_endpoint*>> placement_result_map;
    std::vector<int> vnf_id_tab;
    std::vector<int> vlink_id_tab;

public:
    // Constructor
    VNC();

    // Modifiers
    void add_vnf(struct vnf& vnf_);
    void add_vlink(struct v_links& vlink_);
    void update_placement_result_map(struct vnf* pvnf, struct v_links* pvlink, struct edge_endpoint* pnode);
    void add_vnc_infos_map(int const & key, std::string const & given_value);
    void update_vnf_placement_status(int const & i, bool const & status);
    void reset();

    // Accessors
    int get_nb_vnf() const;
    int get_nb_vlinks() const;
    std::vector<int> get_vnf_id_tab() const;
    std::vector<int> get_vlink_id_tab() const;
    struct vnf* get_vnf_by_id(int const & i);
    struct v_links* get_vlink_by_id(int const & i);
    std::map<std::string, std::string> get_vnc_infos_map() const;
    std::map<int, bool> get_vnf_placement_status() const;
    bool get_singlevnf_placement_status(int const & i);
    std::map<int, struct vlink_support> get_vlink_process_status() const;
    struct vlink_support* get_vlink_support(int const & i);

    // Other methods
    std::string get_vnc_recap();
    bool check_vlink_existence(struct vnf* source_, struct vnf* dest);
};



/*
  Other useful functions created for the entire implementation
*/
bool find_element_in_tab(std::vector<int> & tab, int const & i);
bool erase_element_in_tab(std::vector<int> & tab, int const & i);

void edge_struct_init(struct edge_struct& edge_, int const & node_,
                        long const & bandwidth_, long const & residual_bandwidth_, int const & delay_, int const & cost_,
                        int const & source_, int const & destination_
);

void edge_endpoint_init(struct edge_endpoint& vertex_, int const & v_id_, int const & available_disk_capacity_,
                         int const & available_ram_, int const & available_cpu_, int const & cost_
);

std::string check_path(Graph & mygraph, int const & i);

bool comparator(std::pair<int, struct edge_endpoint>& a, std::pair<int, struct edge_endpoint>& b);
std::vector<int> sort_vertices_by_resources(std::map<int, struct edge_endpoint>& vmap);

void save_vnfplacement_result(std::string const & result_);
std::string get_sys_datetime();
std::string format_string(int & field_length, std::string & field_value);

int get_elt_index(std::vector<int>& vec, int const & elt);
int find_convenient_node_for_vnf(struct vnf* vnf_, Graph & graph_, std::vector<int> & path_);
bool vlink_supported_by_edge(Graph & graph_, VNC* vnc_, int const & vlink_, int const & edge_src, int const & edge_dst);
void dac_with_vlinks_tab(VNC* myvnc, Graph & mygraph, std::vector<int> & vlink_id_tab);
bool vnf_placement_in_graph(Graph & mygraph_, std::vector<int> & sorted_vertices, VNC* myvnc, struct report_recap* recap_ptr);
//std::string vnf_placement_in_graph(Graph & mygraph_, std::vector<int> & sorted_vertices, std::map<int, VNC> & vnc_map);
std::string requests_placement_process(Graph & mygraph_,// std::vector<int> & sorted_vertices,
                                       std::map<int, struct edge_endpoint> & vertices_map,
                                       std::map<int, VNC> & vnc_map//, std::map<int, struct report_recap> & trequests_recap_map
);

void infra_and_requests_mass_loading(std::map<int, struct edge_struct>& edges_map,
                                        std::map<int, struct edge_endpoint>& vertices_map,
                                        //std::map<int, struct v_links>& vlinks_map, std::map<int, struct vnf>& vnf_map,
                                        Graph & mygraph, std::map<int, VNC>& vnc_map
);
std::vector<std::string> split_string_genesis(const std::string &text, const int &key);
void split_string(std::map<std::string, std::string> &mymap, const std::string &text, char sep);
void split_string_v2(std::map<std::string, std::string> &mymap, const std::string &text, char sep);
void split_string_links_v2(std::map<std::vector<std::string>, std::string> &mymap, const std::string &text, char sep);
void split_string_v3(std::vector<std::string> & myvec, std::string &text, char sep);
void nodes_mass_loading(std::map<int, struct edge_endpoint>& vertices_map, std::string &text);
void phys_links_mass_loading(std::map<int, struct edge_struct>& edges_map, std::string &text);
void vnf_mass_loading(int const & i, std::map<int, struct vnf>& vnf_map, std::string &text);
void vnc_links_mass_loading(int const & i, VNC* myvnc, std::map<int, struct v_links>& vlinks_map, std::string &text);

#endif // DATA_STRUCTURE_H_INCLUDED
