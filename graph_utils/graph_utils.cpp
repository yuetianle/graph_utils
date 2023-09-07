// graph_utils.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "tf_topo_graph_t.h"


int main()
{
	tf_topo_graph_t graph_data;
	tf_topo_vertex_t tf_topo_1;
	tf_topo_vertex_t tf_topo_2;
	tf_topo_vertex_t tf_topo_2_link;
	tf_topo_vertex_t tf_topo_2_link1;
	tf_topo_vertex_t tf_topo_3;
	tf_topo_vertex_t tf_topo_4;
	tf_topo_vertex_t tf_topo_5;
	tf_topo_vertex_t tf_topo_6;
	tf_topo_vertex_t tf_topo_7;
	tf_topo_vertex_t tf_topo_8;
	tf_topo_vertex_t tf_topo_9;

	tf_topo_vertex_t tf_topo_second_one;
	tf_topo_vertex_t tf_topo_second_two;
	tf_topo_vertex_t tf_topo_second_three;
	tf_topo_1.BranchID = "1";
	tf_topo_1.BranchName = "母线1";
	tf_topo_1.NodeBegin = 1;

	tf_topo_2.BranchID = "2";
	tf_topo_2.BranchName = "变压器2";
	tf_topo_2.NodeBegin = 2;
	tf_topo_2.NodeEnd = 1;
	tf_topo_2.NodeThird = 21;

	tf_topo_2_link.BranchID = "2_1";
	tf_topo_2_link.BranchName = "线路2_1";
	tf_topo_2_link.NodeBegin = 21;
	tf_topo_2_link.NodeEnd = 22;

	tf_topo_2_link1.BranchID = "2_2";
	tf_topo_2_link1.BranchName = "线路2_2";
	tf_topo_2_link1.NodeBegin = 22;
	tf_topo_2_link1.NodeEnd = 23;

	tf_topo_3.BranchID = "3";
	tf_topo_3.BranchName = "断路器3";
	tf_topo_3.NodeBegin = 2;
	tf_topo_3.NodeEnd = 3;

	tf_topo_4.BranchID = "4";
	tf_topo_4.BranchName = "母线4";
	tf_topo_4.NodeBegin = 3;

	tf_topo_5.BranchID = "5";
	tf_topo_5.BranchName = "断路器5";
	tf_topo_5.NodeBegin = 3;
	tf_topo_5.NodeEnd = 4;

	tf_topo_6.BranchID = "6";
	tf_topo_6.BranchName = "母线6";
	tf_topo_6.NodeBegin = 4;

	tf_topo_7.BranchID = "7";
	tf_topo_7.BranchName = "断路器7";
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

tf_topo_second_one.BranchID = "10";
	tf_topo_second_one.BranchName = "母线10";
	tf_topo_second_one.NodeBegin = 10;

	tf_topo_second_two.BranchID = "11";
	tf_topo_second_two.BranchName = "线路11";
	tf_topo_second_two.NodeBegin = 10;
	tf_topo_second_two.NodeEnd = 11;

	tf_topo_second_three.BranchID = "12";
	tf_topo_second_three.BranchName = "断路器12";
	tf_topo_second_three.NodeBegin = 11;
	tf_topo_second_three.NodeEnd = 12;	graph_data.add_topo_node(tf_topo_1);
	graph_data.add_topo_node(tf_topo_2);
	graph_data.add_topo_node(tf_topo_2_link);
	graph_data.add_topo_node(tf_topo_2_link1);
	graph_data.add_topo_node(tf_topo_3);
	graph_data.add_topo_node(tf_topo_4);
	graph_data.add_topo_node(tf_topo_5);
	graph_data.add_topo_node(tf_topo_6);
	graph_data.add_topo_node(tf_topo_7);
	graph_data.add_topo_node(tf_topo_8);
	graph_data.add_topo_node(tf_topo_9);

	graph_data.add_topo_node(tf_topo_second_one);
	graph_data.add_topo_node(tf_topo_second_two);
	graph_data.add_topo_node(tf_topo_second_three);

	tf_topo_edge_t edge;
	edge.link_node = tf_topo_1.NodeBegin;
	graph_data.add_topo_edge(tf_topo_1.BranchID, tf_topo_2.BranchID, edge);
	graph_data.add_topo_edge(tf_topo_1.BranchID, tf_topo_2.BranchID, edge);
	edge.link_node = tf_topo_2.NodeBegin;
	graph_data.add_topo_edge(tf_topo_2.BranchID, tf_topo_3.BranchID, edge);

	edge.link_node = tf_topo_2_link.NodeBegin;
	graph_data.add_topo_edge(tf_topo_2.BranchID, tf_topo_2_link.BranchID, edge);

	edge.link_node = tf_topo_2_link1.NodeBegin;
	graph_data.add_topo_edge(tf_topo_2_link.BranchID, tf_topo_2_link1.BranchID, edge);

	edge.link_node = tf_topo_3.NodeEnd;
	graph_data.add_topo_edge(tf_topo_3.BranchID, tf_topo_4.BranchID, edge);
	edge.link_node = tf_topo_4.NodeBegin;
	graph_data.add_topo_edge(tf_topo_4.BranchID, tf_topo_5.BranchID, edge);
	edge.link_node = tf_topo_5.NodeEnd;
	graph_data.add_topo_edge(tf_topo_5.BranchID, tf_topo_6.BranchID, edge);
	edge.link_node = tf_topo_6.NodeBegin;
	graph_data.add_topo_edge(tf_topo_6.BranchID, tf_topo_7.BranchID, edge);
	edge.link_node = tf_topo_7.NodeEnd;
	graph_data.add_topo_edge(tf_topo_7.BranchID, tf_topo_8.BranchID, edge);
	edge.link_node = tf_topo_9.NodeBegin;
	graph_data.add_topo_edge(tf_topo_8.BranchID, tf_topo_9.BranchID, edge);

	edge.link_node = tf_topo_second_one.NodeBegin;
	graph_data.add_topo_edge(tf_topo_second_one.BranchID, tf_topo_second_two.BranchID, edge);
	edge.link_node = tf_topo_second_two.NodeEnd;
	graph_data.add_topo_edge(tf_topo_second_two.BranchID, tf_topo_second_three.BranchID, edge);
	std::string file_name = "test.dot";
	graph_data.print_topo_node_info();
	TF_TOPO_VERTEX_DES_QUEUE topo_vertex_queue;
	std::queue<std::string> branch_ids;
	graph_data.breadth_first(tf_topo_4.BranchID, &branch_ids);
	graph_data.write_file(file_name);
	auto topo_branch_count = graph_data.topo_branchs_num();
	auto topo_branch_edge_count = graph_data.topo_edges_num();
	printf("branch:%d edge_count:%d", topo_branch_count, topo_branch_edge_count);

	std::set<std::string> graph_one_branchs;
	graph_data.get_connect_branch_ids_by_id(tf_topo_1.BranchID, &graph_one_branchs);
	graph_one_branchs.clear();
	graph_data.find_connected_branchs_ids(tf_topo_1.BranchID, &graph_one_branchs);
    return 0;
}

