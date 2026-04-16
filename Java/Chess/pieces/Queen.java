package pieces;

import java.util.ArrayList;

import main.GamePanel;

public class Queen extends Piece {

	public Queen(int row, int col, boolean isWhite, GamePanel panel){
		super(row, col, isWhite, panel);
		type = PieceType.QUEEN;
		image = panel.setImg(type, isWhite);	
	}

	@Override
	public ArrayList<Move> getMoves() {
		//straight path
		getPath(0, 1);
		getPath(1, 0);
		getPath(0, -1);
		getPath(-1, 0);
		//Diagonal path
		getPath(1, 1);
		getPath(1, -1);
		getPath(-1, -1);
		getPath(-1, 1);

		return moves;
	}
}
