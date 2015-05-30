#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <queue>

#define WHITE 1
#define GREY 2
#define BLACK 3

class Graph {
		int _v;
		std::vector< std::vector< std::pair<int, int> > >  _list;
		std::vector< int > _path;
	public:
		Graph(int V) : _list(V), _path(V) { 
			_v = V;
		}
		void addE(int u, int v) {
			_list[u].push_back(std::make_pair(v, 1));
			_list[v].push_back(std::make_pair(u, 1));
		}

		void flow(int u, int v) {
			std::vector< std::pair<int, int> >::iterator j;
			for (j = _list[v].begin(); j != _list[v].end(); ++j) {
				if ((*j).first == u) {
					(*j).second--;
					break;
				}
			}
		}

		int ford_ful(std::vector<int> sol) {
			std::vector<int>::iterator j = sol.begin();
			int i, max_flow = 0;
			j = sol.begin();
			j++;
			std::vector<int>::iterator h = j+1;
			int max_flow_aux = 0;
			max_flow = -1;
			for (;j != sol.end(); j++) {
				h = j + 1;
				for (; h != sol.end(); h++) {
					if (j != h) {
						while(BFS(*h, *j)) {
							i = *j;
							while (i != *h) {
								flow(i, _path[i]);
								i = _path[i];
							}
							max_flow_aux++;
						}
						if (max_flow == -1) {
							max_flow = max_flow_aux;
						}
						else {
							if (max_flow_aux < max_flow) {
								max_flow = max_flow_aux;
							}
						}
						refresh();
						max_flow_aux = 0;
					}
				}
			}
			return max_flow;
		}

		int BFS(int start, int end) {
			int i;
			int color[_v];
			int d[_v];
			std::queue<int> queue;
			std::vector< std::pair<int, int> >::iterator j;
			for ( i = 0; i < _v; i++) {
				d[i] = -1;
				color[i] = WHITE;
				_path[i] = -1;
			}
			i = start;
			d[i] = 0;
			color[i] = GREY;
			queue.push(i);
			while (!queue.empty()) {
				i = queue.front();
				queue.pop();
				if (i == end) {
					return 1;
				}
				for(j = _list[i].begin(); j != _list[i].end(); j++) {
					if((*j).second != 0) {
						if (color[(*j).first] == WHITE) {
							color[(*j).first] = GREY;
							d[(*j).first] = d[i] + 1;
							_path[(*j).first] = i;
							queue.push((*j).first);
						}
						color[i] = BLACK;
					}
				}
			}
			return 0;
		}
		
		void refresh() {
			int i;
			std::vector< std::pair<int, int> >::iterator aux;
			for (i = 0; i < _v; i++) {
				for (aux = _list[i].begin(); aux != _list[i].end(); aux++) {
					(*aux).second = 1;
				}
			}
		}
};

int main() {
	int V, E, i, u, v, h, n;
	std::cin >> V >> E;
	Graph g(V);
	for(i = 0; i < E; i++) {
		std::cin >> u >> v;
		g.addE(u, v);
	}
	
	std::string line;
	std::cin >> h;
	std::getline(std::cin, line);
	std::vector< std::vector<int> > p(h);
	for (i = 0; i < h; i++) {
		std::getline(std::cin, line);
		std::istringstream in(line, std::istringstream::in);
		while (in >> n) {
			p[i].push_back(n);
		}
	}

	for (i = 0; i < h; i++) {
		std::cout << g.ford_ful(p[i]) << std::endl;
		g.refresh();
	}
	return 0;
}