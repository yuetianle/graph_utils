// graph_utils.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "tf_topo_graph_t.h"


int main()
{
	tf_topo_graph_t graph_data;
	tf_topo_vertex_t tf_topo_1;
	tf_topo_vertex_t tf_topo_2;
	tf_topo_vertex_t tf_topo_3;
	tf_topo_vertex_t tf_topo_4;
	tf_topo_vertex_t tf_topo_5;
	tf_topo_vertex_t tf_topo_6;
	tf_topo_vertex_t tf_topo_7;
	tf_topo_vertex_t tf_topo_8;
	tf_topo_vertex_t tf_topo_9;
	tf_topo_1.BranchID = "1";
	tf_topo_1.BranchName = "母线1";
	tf_topo_1.NodeBegin = 1;

	tf_topo_2.BranchID = "2";
	tf_topo_2.BranchName = "变压器2";
	tf_topo_2.NodeBegin = 2;
	tf_topo_2.NodeEnd = 1;
	tf_topo_2.NodeThird = 1;

	tf_topo_3.BranchID = "3";
	tf_topo_3.BranchName = "短路器3";
	tf_topo_3.NodeBegin = 2;
	tf_topo_3.NodeEnd = 3;

	tf_topo_4.BranchID = "4";
	tf_topo_4.BranchName = "母线4";
	tf_topo_4.NodeBegin = 3;

	tf_topo_5.BranchID = "5";
	tf_topo_5.BranchName = "短路器5";
	tf_topo_5.NodeBegin = 3;
	tf_topo_5.NodeEnd = 4;

	tf_topo_6.BranchID = "6";
	tf_topo_6.BranchName = "母线6";
	tf_topo_6.NodeBegin = 4;

	tf_topo_7.BranchID = "7";
	tf_topo_7.BranchName = "短路器7";
	tf_topo_7.NodeBegin = 4;
	tf_topo_7.NodeEnd = 5;

	tf_topo_8.BranchID = "8";
	tf_topo_8.BranchName = "变压器8";
	tf_topo_8.NodeBegin = 5;
	tf_topo_8.NodeEnd = 6;
	tf_topo_8.NodeThird = 6;

	tf_topo_9.BranchID = "9";
	tf_topo_9.BranchName = "母线9";
	tf_topo_9.NodeBegin = 6;


		
	graph_data.add_topo_node(tf_topo_1);
	graph_data.add_topo_node(tf_topo_2);
	graph_data.add_topo_node(tf_topo_3);
	graph_data.add_topo_node(tf_topo_4);
	graph_data.add_topo_node(tf_topo_5);
	graph_data.add_topo_node(tf_topo_6);
	graph_data.add_topo_node(tf_topo_7);
	graph_data.add_topo_node(tf_topo_8);
	graph_data.add_topo_node(tf_topo_9);
	tf_topo_edge_t edge;
	edge.node_begin = tf_topo_1.NodeBegin;
	graph_data.add_topo_edge(tf_topo_1.BranchID, tf_topo_2.BranchID, edge);
	graph_data.add_topo_edge(tf_topo_1.BranchID, tf_topo_2.BranchID, edge);
	edge.node_begin = tf_topo_1.NodeEnd;
	graph_data.add_topo_edge(tf_topo_2.BranchID, tf_topo_3.BranchID, edge);
	edge.node_begin = tf_topo_2.NodeEnd;
	graph_data.add_topo_edge(tf_topo_3.BranchID, tf_topo_4.BranchID, edge);
	edge.node_begin = tf_topo_4.NodeBegin;
	graph_data.add_topo_edge(tf_topo_4.BranchID, tf_topo_5.BranchID, edge);
	edge.node_begin = tf_topo_5.NodeEnd;
	graph_data.add_topo_edge(tf_topo_5.BranchID, tf_topo_6.BranchID, edge);
	edge.node_begin = tf_topo_6.NodeBegin;
	graph_data.add_topo_edge(tf_topo_6.BranchID, tf_topo_7.BranchID, edge);
	edge.node_begin = tf_topo_7.NodeEnd;
	graph_data.add_topo_edge(tf_topo_7.BranchID, tf_topo_8.BranchID, edge);
	edge.node_begin = tf_topo_9.NodeBegin;
	graph_data.add_topo_edge(tf_topo_8.BranchID, tf_topo_9.BranchID, edge);
	std::string file_name = "test.dot";
	graph_data.print_topo_node_info();
	graph_data.write_file(file_name);
    return 0;
}

