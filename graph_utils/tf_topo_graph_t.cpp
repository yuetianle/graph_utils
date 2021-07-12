#include "stdafx.h"
#include "tf_topo_graph_t.h"


tf_topo_graph_t::tf_topo_graph_t()
{
}


tf_topo_graph_t::~tf_topo_graph_t()
{
}

std::string tf_topo_graph_t::add_topo_node(tf_topo_vertex_t vertex_data)
{
	std::string branch_id = vertex_data.BranchID;
	auto find_data = _vertex_map.find(branch_id);
	if (find_data != _vertex_map.end())
	{
		printf("error same branch %s", branch_id.c_str());
		return "";
	}
	else
	{
		TF_TOPO_VERTEX_T topo_node(vertex_data);
		TF_TOPO_VERTEX_DES vertex_des = boost::add_vertex(topo_node, _topo_graph);
		_vertex_map.insert(std::make_pair(branch_id, vertex_des));
		return branch_id;
	}
}

std::string tf_topo_graph_t::add_topo_edge(const std::string &start_topo_node_id, const std::string &end_topo_node_id, const tf_topo_edge_t &edge_data)
{
	if (start_topo_node_id.empty() || end_topo_node_id.empty())
	{
		return "";
	}
	auto find_start_item = _vertex_map.find(start_topo_node_id);
	auto find_end_item = _vertex_map.find(end_topo_node_id);
	TF_TOPO_EDGE_T topo_edge_data(edge_data);
	if (find_start_item != _vertex_map.end() && find_end_item != _vertex_map.end())
	{
		std::pair<TF_TOPO_EDGE_DES, bool> edge_des = boost::add_edge(find_start_item->second, find_end_item->second, topo_edge_data, _topo_graph);
		return "";
	}
	else
	{
		printf("not existed this node");
		return "";
	}
}

bool tf_topo_graph_t::write_file(const std::string &file_name)
{
	if (file_name.empty())
	{
		return false;
	}
	else
	{
		std::ofstream out(file_name.c_str());
		topo_vertex_writer<TOPO_GRAPH> vertex_writer(_topo_graph);
		//auto vertex_writer = boost::make_label_writer("name");
		boost::write_graphviz(out, _topo_graph, vertex_writer, boost::default_writer());
		//boost::write_graphviz(out, _topo_graph, boost::make_label_writer(boost::get(boost::vertex_name, _topo_graph)));
		return true;
	}
}

void tf_topo_graph_t::print_topo_node_info()
{
	std::pair<TF_TOPO_VERTEX_ITER, TF_TOPO_VERTEX_ITER> vertex_pair = boost::vertices(_topo_graph);
	for (auto item= vertex_pair.first; item != vertex_pair.second; ++item)
	{
		TF_TOPO_VERTEX_DES node_desc = *item;
		TF_TOPO_VERTEX_T data = _topo_graph[node_desc];
		std::string branch_name = data.BranchName;
		printf("data branch_id:%s name:%s\r\n", data.BranchID.c_str(), branch_name.c_str());
	}
}

void tf_topo_graph_t::breadth_first(const std::string& branch_id, TF_TOPO_VERTEX_DES_QUEUE *topo_vertex_queue)
{
	if (branch_id.empty() || !topo_vertex_queue)
	{
		return;
	}
	auto find_item = _vertex_map.find(branch_id);

	tf_topo_bfs_visitor_t topo_bfs_visitor(*topo_vertex_queue);
	if (find_item != _vertex_map.end())
	{
		boost::breadth_first_search(_topo_graph, find_item->second, boost::visitor(topo_bfs_visitor));
	}
}

void tf_topo_graph_t::breadth_first(const std::string& branch_id, std::queue<std::string> *branch_id_queue)
{
	if (branch_id.empty() || !branch_id_queue)
	{
		return;
	}
	auto find_item = _vertex_map.find(branch_id);

	TF_TOPO_VERTEX_DES_QUEUE topo_vertex_queue;
	tf_topo_bfs_visitor_t topo_bfs_visitor(topo_vertex_queue);
	if (find_item != _vertex_map.end())
	{
		boost::breadth_first_search(_topo_graph, find_item->second, boost::visitor(topo_bfs_visitor));
	}
	while (!topo_vertex_queue.empty())
	{
		TF_TOPO_VERTEX_T data = _topo_graph[topo_vertex_queue.front()];
		branch_id_queue->push(data.BranchID);
		printf("branch_id:%s name:%s\r\n --->", data.BranchID.c_str(), data.BranchName.c_str());
		topo_vertex_queue.pop();
	}

}

void tf_topo_graph_t::dfs_first(const std::string& branch_id, TF_TOPO_VERTEX_DES_QUEUE *topo_vertex_queue)
{
	if (branch_id.empty() || !topo_vertex_queue)
	{
		return;
	}
	auto find_item = _vertex_map.find(branch_id);

	tf_topo_dfs_visitor_t topo_dfs_visitor(*topo_vertex_queue);
	if (find_item != _vertex_map.end())
	{
		//boost::depth_first_search(_topo_graph, find_item->second, boost::visitor(topo_dfs_visitor));
	}

}

void tf_topo_graph_t::dfs_first(const std::string& branch_id, std::queue<std::string> *branch_id_queue)
{
	if (branch_id.empty() || !branch_id_queue)
	{
		return;
	}
	auto find_item = _vertex_map.find(branch_id);

	TF_TOPO_VERTEX_DES_QUEUE topo_vertex_queue;
	tf_topo_dfs_visitor_t topo_dfs_visitor(topo_vertex_queue);
	if (find_item != _vertex_map.end())
	{
		std::vector<boost::default_color_type> color_map(boost::num_vertices(_topo_graph));
		//boost::make_iterator_property_map(std::begin(color_map), boost::get(boost::vertex_name_t, _topo_graph), color_map[0]);
		//boost::depth_first_search(_topo_graph, boost::visitor(topo_dfs_visitor), color_map, find_item->second);
		//boost::depth_first_search(_topo_graph, find_item->second, boost::visitor(topo_dfs_visitor));
	}
	while (!topo_vertex_queue.empty())
	{
		TF_TOPO_VERTEX_T data = _topo_graph[topo_vertex_queue.front()];
		branch_id_queue->push(data.BranchID);
		printf("branch_id:%s name:%s\r\n --->", data.BranchID.c_str(), data.BranchName.c_str());
		topo_vertex_queue.pop();
	}
}
