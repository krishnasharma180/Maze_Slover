#include <bits/stdc++.h>
using namespace std;

bool found=false;

void maze(vector<vector<char>>& m) {
    m = {
        {'S',' ',' ',' ','#','#','#','#','#','#'},
        {' ','#','#',' ','#','#','#','#','#','#'},
        {' ','#','#',' ','#',' ',' ','#','#','#'},
        {' ','#','#',' ',' ',' ','#','#','#','#'},
        {' ','#',' ','#','#',' ','#','#','#','#'},
        {' ','#',' ','#','#',' ',' ',' ','E','#'},
        {' ','#','#','#','#',' ','#','#','#','#'},
        {' ','#','#','#','#',' ','#',' ','#','#'},
        {' ','#','#','#','#',' ','#',' ','#','#'},
        {' ',' ',' ',' ',' ',' ','#','#','#','#'}
    };

    cout << "Maze:\n";
    for (auto &row : m) {
        for (char c : row) cout << c << " ";
        cout << "\n";
    }
}

struct Node{
    int x,y;
    vector<pair<int,int>> path;
};

void dfs(vector<vector<char>> &maze) {
    int n = maze.size(), m = maze[0].size();
    stack<Node> frontier;
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    frontier.push({0, 0, {{0, 0}}});
    visited[0][0] = true;

    while (!frontier.empty()) {
        Node curr = frontier.top();
        frontier.pop();

        if (maze[curr.x][curr.y] == 'E') {
            cout << "Found the exit!" << endl;

            // mark final path with '*'
            for (auto val : curr.path) {
                if (maze[val.first][val.second] != 'E')
                    maze[val.first][val.second] = '*';
            }

            return;
        }

        pair<int,int> dirs[] = {{0,-1},{-1,0},{0,1},{1,0}}; 
        for (auto dir : dirs) {
            int nx = curr.x + dir.first;
            int ny = curr.y + dir.second;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                // cout<<nx<<ny<<endl;
                maze[nx][ny] != '#' && !visited[nx][ny]) {
                Node next = {nx, ny, curr.path};
                next.path.push_back({nx, ny});
                frontier.push(next);
                visited[nx][ny] = true;
            }
        }
    }

    cout << "Path not found!!" << endl;
}

void bfs(vector<vector<char>>& maze){
   int n=maze.size(),m=maze[0].size();
   queue<Node> q;
    Node start={0,0,{{0,0}}};
    q.push(start);
    while(!q.empty()){
        Node current=q.front();
        q.pop();
        vector<vector<bool>> visited(n,vector<bool>(m,false));
        if(maze[current.x][current.y]=='E'){
            cout<<"Found the exit!"<<endl;
            found=true;
            for(auto val:current.path){
                maze[val.first][val.second]='.';
            }
            return;
        }
    
        //Exploring neighbours using loop
        pair<int,int> directions[]={{1,0},{0,-1},{-1,0},{0,1}}; 
        for(int i=0;i<4;i++){
            int nx=current.x+directions[i].first;
            int ny=current.y+directions[i].second;
            if(nx>=0&&nx<n&&ny>=0&&ny<m&&maze[nx][ny]!='#'&&!visited[nx][ny]){
                Node next={nx,ny,current.path};
                next.path.push_back({nx,ny});
                q.push(next);
                visited[nx][ny]=true;
            }
        }

}
   cout<<"Path not found!!"<<endl;
}

int main(){
  int choice=0;
  vector<vector<char>> maz;
  while(choice!=-1){
      maze(maz);
      cout<<"Enter 1 for DFS and 2 for BFS: ";
      cin>>choice;
      if(choice==1){
      dfs(maz);
  }else if(choice==2){
      bfs(maz);
  }
    cout<<"Maze after "<<(choice==1 ? "DFS" : "BFS")<<":"<<endl;
    for(auto val:maz){
        for(auto i:val){
            cout<<i<<" ";
        }
        cout<<endl;
    }

  }

  return 0;
}