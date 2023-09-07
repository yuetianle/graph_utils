
#ifndef _tf_graph_t_h_
#define _tf_graph_t_h_

#include <set>
#include <queue>
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graphviz.hpp"
#include "boost/graph/depth_first_search.hpp"
#include "boost/graph/breadth_first_search.hpp"
#include "boost/graph/visitors.hpp"
#include "boost/graph/visitors.hpp"
#include "boost/graph/breadth_first_search.hpp"
#include "bf_string_utils.h"

struct tf_topo_edge_t
{
public:
	tf_topo_edge_t()
		:link_node(-1)
	{}
	int link_node;
};

//enum GRAPHTYPE
//{
//	GT_STATION,///<厂站图
//	GT_POWER_LINK,///< 供电图
//	GT_WHOLE///< 全网图
//};

struct tf_graph_desc_t
{
public:
	std::string description;
};

struct tf_topo_vertex_t
{
public:
	tf_topo_vertex_t()
		:BranchID(""), BranchName(""), Substation(""), Substation2(""), NodeBegin(-1), NodeEnd(-1), NodeThird(-1), NeutralPoint(-1)\
		, neutralBegin(-1), neutralEnd(-1), neutralThird(-1), Type(-1), SubUnitID("")
	{}
	std::string	BranchID; /**< 支路ID */
	std::string	BranchName; /**< 支路名字 */
	std::string	Substation; /**< 首厂站 */
	std::string Substation2; /**< 末厂站 */
	long		NodeBegin; /**< 变压器高压节点 */
	long		NodeEnd; /**< 变压器低压节点 */
	long		NodeThird; /**< 变压器中压节点 */
	long		NeutralPoint; /**< 变压器中性节点号 */

	long		neutralBegin;
	long		neutralEnd;
	long		neutralThird;

	int		Type; /**< 类型 */

	std::string SubUnitID;
};

//typedef boost::property<boost::edge_name_t, tf_topo_edge_t> TF_TOPO_EDGE_T;
//typedef boost::property<boost::vertex_name_t, tf_topo_vertex_t> TF_TOPO_VERTEX_T;
//typedef boost::property<boost::graph_name_t, tf_graph_desc_t> TF_GRAPH_T;

typedef tf_topo_edge_t TF_TOPO_EDGE_T;
typedef tf_topo_vertex_t TF_TOPO_VERTEX_T;
typedef tf_graph_desc_t TF_GRAPH_T;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, TF_TOPO_VERTEX_T, TF_TOPO_EDGE_T, TF_GRAPH_T> TOPO_GRAPH;
typedef boost::graph_traits<TOPO_GRAPH>::vertex_descriptor TF_TOPO_VERTEX_DES;
typedef std::queue<TF_TOPO_VERTEX_DES> TF_TOPO_VERTEX_DES_QUEUE;
typedef boost::graph_traits<TOPO_GRAPH>::edge_descriptor TF_TOPO_EDGE_DES;
typedef boost::graph_traits<TOPO_GRAPH>::vertex_iterator TF_TOPO_VERTEX_ITER;
typedef boost::graph_traits<TOPO_GRAPH>::edge_iterator TF_TOPO_EDGE_ITER;

template <class Name>
class topo_vertex_writer {
public:
	topo_vertex_writer(Name _name) : name(_name) {}
	template <class VertexOrEdge>
	void operator()(std::ostream& out, const VertexOrEdge& v) const {
		std::string data = name[v].BranchName;
		if (!BF_COMMON::bf_is_utf8(data.c_str()))
		{
			data = BF_COMMON::bf_to_utf8(data);
		}
		data = name[v].BranchID + ":"+ data;
		std::cout << "name:" << data << std::endl;		//out << "[label=\"" << name[v].BranchName << "\"]";
		out << "[label=\"" << data << "\"]";
	}
private:
	Name name;
};
template <class Name>
class topo_edge_writer {
public:
	topo_edge_writer(Name _name) : name(_name) {}
	template <class VertexOrEdge>
	void operator()(std::ostream& out, const VertexOrEdge& v) const {
		auto data = name[v].link_node;
		//out << "[label=\"" << name[v].BranchName << "\"]";
		out << "[label=\"" << data << "\"]";
	}
private:
	Name name;
};

class topo_graph_writer {
public:
	void operator()(std::ostream &out)
	{
		out << "graph [bgcolor=lightgrey]" << std::endl;
		out << "node [shape=circle color=white fontname=FangSong]" << std::endl;
		out << "edge [style=dashed]" << std::endl;
	}
};

struct TopoNodeInfo
{
	TopoNodeInfo()
		:branch_id(""), topo_type(-1)
	{}
	std::string branch_id;
	int topo_type;
	bool operator < (const TopoNodeInfo &other) const
	{
		return (topo_type < other.topo_type) || (topo_type == other.topo_type && branch_id.compare(other.branch_id) < 0);
	}
	bool operator == (const TopoNodeInfo &other) const
	{
		return (branch_id == other.branch_id && topo_type == other.topo_type);
	}
};

template<typename Graph>
class bfs_topo_graph_visitor : public boost::default_bfs_visitor
{
public:
	typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexDescriptor;
	typedef typename boost::graph_traits<Graph>::edge_descriptor EdgeDescriptor;
	bfs_topo_graph_visitor(std::vector<VertexDescriptor> &nodes_visited)
		:m_nodes_visited(nodes_visited)
	{}
	void tree_edge(EdgeDescriptor e, const Graph& g)
	{
		VertexDescriptor u = boost::source(e, g);
		VertexDescriptor v = boost::target(e, g);
		m_nodes_visited.push_back(v);
	}
private:
	std::vector<VertexDescriptor> &m_nodes_visited;
};
class tf_topo_bfs_visitor_t : public boost::default_bfs_visitor
{
public:
	tf_topo_bfs_visitor_t(TF_TOPO_VERTEX_DES_QUEUE &visited_): visited(visited_)
	{}
	void discover_vertex(TF_TOPO_VERTEX_DES s, const TOPO_GRAPH &g)
	{

		TF_TOPO_VERTEX_T data = g[s];
		printf("--->%s", data.BranchID.c_str());
		visited.push(s);
	}
	TF_TOPO_VERTEX_DES_QUEUE &visited;
};

class tf_topo_dfs_visitor_t : public boost::default_dfs_visitor
{
public:
	tf_topo_dfs_visitor_t(TF_TOPO_VERTEX_DES_QUEUE &visited_): visited(visited_)
	{}
	void discover_vertex(TF_TOPO_VERTEX_DES s, const TOPO_GRAPH &g)
	{

		TF_TOPO_VERTEX_T data = g[s];
		printf("--->%s", data.BranchID.c_str());
		visited.push(s);
	}
	TF_TOPO_VERTEX_DES_QUEUE visited;
};
class tf_topo_graph_t
{
public:
	tf_topo_graph_t();
	~tf_topo_graph_t();
	std::string add_topo_node(tf_topo_vertex_t vertex_data);
	//std::string remove_vertex(const std::string &vertex_id);
	std::string add_topo_edge(const std::string &start_topo_node_id, const std::string &end_topo_node_id, const tf_topo_edge_t &edge_data);
	/**
	 * @brief topo_branchs_num 获取topo图的所有设备个数
	 * @return size_t 
	 */
	size_t topo_branchs_num();
	/**
	 * @brief topo_edges_num 获取topo图连接的边的个数
	 * @return size_t 
	 */
	size_t topo_edges_num();
	size_t get_connect_branch_ids_by_id(const std::string& branch_id, std::set<std::string> *find_branchs_ids);
	size_t find_connected_branchs_ids(const std::string& branch_id, std::set<std::string> *find_branchs_ids);
	/**
	 * @brief get_substation_by_branch_id 根据id获取场站id
	 * @param [in] branch_id 设备id
	 * @param [in] station_ids 场站ids
	 * @return size_t 场站个数
	 */
	size_t get_substation_by_branch_id(const std::string& branch_id, std::set<std::string> *station_ids);
	/**
	 * @brief get_link_bus_by_branch_id 根据id获取所有连接母线id
	 * @param [in] branch_id 设备id
	 * @param [in] bus_ids 母线ids
	 * @return size_t 母线个数
	 */
	size_t get_link_bus_by_branch_id(const std::string& branch_id, std::set<std::string> *bus_ids);
	bool write_file(const std::string &file_name);
	void print_topo_node_info();
	/*
	 * @brief 广度优先遍历
	 * 
	*/
	void breadth_first(const std::string& branch_id, TF_TOPO_VERTEX_DES_QUEUE *topo_vertex_queue);
	void breadth_first(const std::string& branch_id, std::queue<std::string> *branch_id_queue);
	void dfs_first(const std::string& branch_id, TF_TOPO_VERTEX_DES_QUEUE *topo_vertex_queue);
	void dfs_first(const std::string& branch_id, std::queue<std::string> *branch_id_queue);
private:
	std::map<std::string, TF_TOPO_VERTEX_DES> _vertex_map;
	std::map<std::string, TF_TOPO_EDGE_DES> _edge_map;
	TOPO_GRAPH _topo_graph;

};


#endif // _tf_graph_t_h_

