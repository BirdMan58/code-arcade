package pieces;

import java.util.ArrayList;

import main.GamePanel;

public class Rook extends Piece {

	public Rook(int row, int col, boolean isWhite, GamePanel panel){
		super(row, col, isWhite, panel);
		type = PieceType.ROOK;
		image = panel.setImg(type, isWhite);	
	}

	@Override
	public ArrayList<Move> getMoves() {

		getPath(0, 1);
		getPath(1, 0);
		getPath(0, -1);
		getPath(-1, 0);

		return moves;
	}
}
