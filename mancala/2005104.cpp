#include<bits/stdc++.h>
using namespace std;

class Mancala{
	public:
	vector<int> player1;
	vector<int> player2;
	int player1Store;
	int player2Store;
	int player1Captured;
	int player2Captured;
	int player1AddMoves;
	int player2AddMoves;
	int curTurn;
	bool gameOver;
	int size;

	Mancala(){
		player1=vector<int>(6,4);
		player2=vector<int>(6,4);
		size=6;
		player1Store=0;
		player1Captured=0;
		player1AddMoves=0;
		player2Store=0;
		player2Captured=0;
		player2AddMoves=0;
		gameOver=false;
	}

	vector<int>& getPlayer(char c){
		if(c == 's'){
            if(curTurn == 1) return player1;
            else return player2;
        }else{
            if(curTurn == 1) return player2;
            else return player1;
        }
	}

	int& getPlayerStore(char c){
        if(c == 's'){
            if(curTurn == 1) return player1Store;
            else return player2Store;
        }else{
            if(curTurn == 1) return player2Store;
            else return player1Store;
        }
    } 

	void isGameOver(){
		int sum1=0;
		int sum2=0;
		for(int i=0;i<player1.size();i++){
			sum1+=player1[i];
		}

		for(int i=0;i<player2.size();i++){
			sum2+=player2[i];
		}

		if(sum1==0 || sum2==0){
			player1Store+=sum1;
			player2Store+=sum2;
			gameOver = true;
			player1=vector<int>(6,0);
			player2=vector<int>(6,0);
		}

	}

	void setCurrentTurn(int turn){
		curTurn=turn;
	}

	int playTurn(int move){
		if(gameOver) return 1;
		if(move>=player1.size()) return 2;

		vector<int>& self= getPlayer('s');
		vector<int>& opponent= getPlayer('o');

		if(self[move]==0) return 2;

		int& selfStore= getPlayerStore('s');
		int& opponentStore=getPlayerStore('o');

		int value= self[move];
		self[move]=0;
		int lastStonePosition=move;

		while(value>0){
			for(int i=move+1;value>0 && i<size;i++){
				self[i]++;
				lastStonePosition=i;
				value--;
			}

			if(value>0){
				selfStore++;
				lastStonePosition=6;
				value--;
			}

			for(int i=0;value>0 && i<size;i++){
				opponent[i]++;
				lastStonePosition=7;
				value--;
			}

			for(int i=0;value>0 && i<size;i++){
				self[i]++;
				lastStonePosition=i;
				value--;
			}
		}

		if(lastStonePosition <= 5 && self[lastStonePosition] == 1 && opponent[size-lastStonePosition-1] != 0){
            if(curTurn == 1){
				player1Captured +=  opponent[size-lastStonePosition-1];
			}else{
				player2Captured +=  opponent[size-lastStonePosition-1];
			} 

            selfStore += self[lastStonePosition] + opponent[size-lastStonePosition-1];
            self[lastStonePosition] = 0;
            opponent[size-lastStonePosition-1] = 0;

        }

		if(lastStonePosition != 6){
            curTurn = curTurn == 1? 2 : 1;
        }else{
            if(curTurn == 1) player1AddMoves++;
            else player2AddMoves++;
        }

		isGameOver();
		return 0;
	}

	int win(){
        if(gameOver){
            if(player1Store == player2Store) return 0;
            return player1Store > player2Store? 1: 2;
        }
        return -1;
    }

    int currentTurn(){
        if(gameOver) return -1;
        return curTurn;
    }


	vector<int> getAvailableMoves(){
        if(gameOver) return vector<int>();

        vector<int>& temp = getPlayer('s');
        vector<int> ans;

        for(int i = 0; i < temp.size(); i++){
            if(temp[i] != 0) ans.push_back(i);
        }
        return ans;
    }
	
	int storageDifference(int self){
		if(self==1){
			return player1Store - player2Store;
		}else{
			return player2Store - player1Store;
		}
	}

	int stonesDifference(int self){
		int sum1=0;
		int sum2=0;
		for(int i=0;i<player1.size();i++){
			sum1+=player1[i];
		}

		for(int i=0;i<player2.size();i++){
			sum2+=player2[i];
		}

		if(self==1){
			return sum1-sum2;
		}else{
			return sum2-sum1;
		}
	}

	int additionalMoves(int self){
		if(self==1){
			return player1AddMoves;
		}else{
			return player2AddMoves;
		}
	}

	int capturedStones(int self){
		if(self==1){
			return player1Captured;
		}else{
			return player2Captured;
		}
	}

	void print(){
		cout<<endl;
		cout<<"        "<<setw(2)<<player2[5]<<" | "<<setw(2)<<player2[4]<<" | "<<setw(2)<<player2[3]<<" | "<<setw(2)<<player2[2]<<" | "<<setw(2)<<player2[1]<<" | "<<setw(2)<<player2[0]<<"  "<<endl;
		cout<<"       ____|____|____|____|____|____     "<<endl;
		cout<<"      "<<"|"<<"                             "<<"|"<<endl;
		cout<<"  "<<setw(2)<<player2Store<<"  "<<"|"<<" P2        MANCALA        P1 "<<"|"<<"  "<<setw(2)<<player1Store<<"  "<<endl;
		cout<<"      "<<"|"<<"_____________________________"<<"|      "<<endl;
		cout<<"           |    |    |    |    |       "<<endl;
		cout<<"        "<<setw(2)<<player1[0]<<" | "<<setw(2)<<player1[1]<<" | "<<setw(2)<<player1[2]<<" | "<<setw(2)<<player1[3]<<" | "<<setw(2)<<player1[4]<<" | "<<setw(2)<<player1[5]<<"  "<<endl;
		cout<<endl;
	}


	friend int heuristics1(Mancala &mancala, int self);
    friend int heuristics2(Mancala &mancala, int self);
    friend int heuristics3(Mancala &mancala, int self);
    friend int heuristics4(Mancala &mancala, int self);

};

int heuristics1(Mancala &mancala, int self){
	return mancala.stonesDifference(self);
}

int heuristics2(Mancala &mancala, int self){
	int w1=rand()%2+1,w2=rand()%2+1;

	return w1*mancala.storageDifference(self)+w2*mancala.stonesDifference(self);
}

int heuristics3(Mancala &mancala,int self){
	int w1=rand()%2+1,w2=rand()%2+1,w3=rand()%2+1;

	return w1* mancala.storageDifference(self)+w2* mancala.stonesDifference(self)
			+w3* mancala.additionalMoves(self);
}

int heuristics4(Mancala &mancala,int self){
	srand(time(0));
	int w1=rand()%2+1,w2=rand()%2+1,w3=rand()%2+1,w4=rand()%2+1;

	return w1* mancala.storageDifference(self)+w2* mancala.stonesDifference(self)
			+w3* mancala.additionalMoves(self)+w4* mancala.capturedStones(self);
}

class AIPlayer{
	const int maximize;
    function<int(Mancala &, int)> heuristic;
	public:
	AIPlayer(int maximize,function<int(Mancala &,int)> heuristic):maximize(maximize) {
		this->heuristic=heuristic;
	}

	int recursion(Mancala &mancala,int depth,int alpha,int beta){
		if(depth==0 || mancala.win()!=-1){
			return heuristic(mancala,maximize);
		}

		if(mancala.currentTurn()==maximize){
			int val=INT32_MIN;
			vector<int> nextMoves=mancala.getAvailableMoves();

			for(auto i:nextMoves){
				Mancala tempBoard=mancala;
				tempBoard.playTurn(i);
				int nodeVal = recursion(tempBoard, depth-1, alpha, beta);

                val = max(nodeVal, val);

                if(val >= beta){
                    break;
                }
                alpha = max(alpha, val);
			}

			return val;
		}else{
			int val=INT32_MAX;
			vector<int> nextMoves=mancala.getAvailableMoves();

			for(auto i:nextMoves){
				Mancala tempBoard=mancala;
				tempBoard.playTurn(i);
				int nodeVal = recursion(tempBoard, depth-1, alpha, beta);
                val = min(nodeVal, val);

                if(val <= alpha){
                    break;
                }
                beta = min(beta, val);
			}

			return val;
		}
		return 0;
	}

	int suggestNextMove(Mancala &mancala,int depth){
		int alpha=INT32_MIN;
		int beta=INT32_MAX;
		int val=INT32_MIN;
		int move=-1;

		vector<int> nextMoves=mancala.getAvailableMoves();

		for(auto i:nextMoves){
			Mancala tempBoard(mancala);
			tempBoard.playTurn(i);
			int nodeVal=recursion(tempBoard,depth-1,alpha,beta);

			if(nodeVal>val){
				move=i;
			}

			val=max(nodeVal,val);
			alpha=max(alpha,val);
		}

		return move;
	}

};

function<int(Mancala&, int)> heuristicks[5] = {
    heuristics1, heuristics1, heuristics2, heuristics3, heuristics4
};

int toss(){
	cout<<"Tossing a coin"<<endl;
	cout<<"Enter 1 for heads and 2 for tails"<<endl;
	int choice;
	cin>>choice;
	srand(time(0));
	int toss=rand()%2+1;
	if(toss==choice){
		cout<<"You won the toss"<<endl;
		return 1;
	}else{
		cout<<"You lost the toss"<<endl;
		return 2;
	}
}

void GameVsComputer(int heuristic){
	int choice = toss();
	int yourTurn;
	int computerTurn;
	if(choice==1){
		yourTurn=1;
		computerTurn=2;
	}else{
		yourTurn=2;
		computerTurn=1;
	}

	Mancala mancala;
	AIPlayer player(computerTurn, heuristicks[heuristic]);
	mancala.setCurrentTurn(1);
	mancala.print();

	while(true){
		int move;
		
		if(mancala.currentTurn() == computerTurn){
			cout<<"Computer's turn"<<endl;
			move=player.suggestNextMove(mancala,10);
			cout<<"Computer played "<<move<<endl;
		}else{
			cout<<"Your turn"<<endl;
			cout<<"Enter your move: ";
			cin>>move;
			cout<<endl;
		}

		if(move==-1){
			break;
		}

		mancala.playTurn(move);
		mancala.print();
		
		if(mancala.win()!=-1){
			cout<<"----Game Over----"<<endl;
			if(yourTurn==1){
				cout<<"Your score  "<<mancala.player1Store<<" :: "<<mancala.player2Store<<"  Computer score"<<endl;
			}else{
				cout<<"Your score  "<<mancala.player2Store<<" :: "<<mancala.player1Store<<"  Computer score"<<endl;
			}
			if(mancala.win()==computerTurn){
				cout<<"Computer wins"<<endl;
			}else{
				cout<<"You win"<<endl;
			}
			break;
		}

	}

}

int ComputerVsComputer(int heuristic1,int heuristic2,int depth,bool print){
	Mancala mancala;
	mancala.setCurrentTurn(1);
	AIPlayer player1(1, heuristicks[heuristic1]);
	AIPlayer player2(2, heuristicks[heuristic2]);
	
	if(print){
		mancala.print();
	}
	while(true){
		int move;
		if(mancala.currentTurn() == 1){
			move = player1.suggestNextMove(mancala, depth);
		}else{
			move = player2.suggestNextMove(mancala, depth);
		}

		if(move==-1){
			break;
		}
		mancala.playTurn(move);
		if(print){
			mancala.print();
		}
		
		if(mancala.win()!=-1){
			if(print){
				cout<<"----Game Over----"<<endl;
				cout<<"Player1  "<<mancala.player1Store<<" :: "<<mancala.player2Store<<"  Player2"<<endl;
			}
			if(mancala.win()==1){
				if(print) cout<<"Player1 wins"<<endl;
				return 1;
			}else{
				if(print) cout<<"Player2 wins"<<endl;
				return 2;
			}
			return 0;
		}
	}

	return 0;

}

void playHundredsOfGames(){
	vector<int> heuristicks(5,0);
	int player1Count;
	int player2Count;
	int drawCount=0;
	int winner;
	cout<<" -----Generating report for 100 games-----"<<endl;
	for(int i=1;i<=4;i++){
		for(int j=i+1;j<=4;j++){
			player1Count=0;
			player2Count=0;
			for(int k=0;k<100;k++){
				int depth=k%6+5;
				winner=ComputerVsComputer(i,j,depth,false);
				if(winner==1){
					player1Count++;
				}else if(winner==2){
					player2Count++;
				}else{
					drawCount++;
				}

			}
			//cout<<"-------------------------------------------------"<<endl;
			cout<<"      Heuristic"<<i<<" --vs-- Heuristic"<<j<<endl;
			cout<<"      Heuristic"<<i<<" wins: "<<player1Count<<endl;
			cout<<"      Heuristic"<<j<<" wins: "<<player2Count<<endl;
			cout<<"      Draws: "<<drawCount<<endl;
			cout<<"-------------------------------------------------"<<endl;
			heuristicks[i]+=player1Count;
			heuristicks[j]+=player2Count;
		}
	}

	cout<<"-----Final Report-----"<<endl;
	for(int i=1;i<=4;i++){
		cout<<"Heuristic"<<i<<" total wins: "<<heuristicks[i]<<endl;
	}

	
}

int main(){
	//GameVsComputer(2);
	ComputerVsComputer(1,1,6,true);
	//playHundredsOfGames();
	return 0;
}