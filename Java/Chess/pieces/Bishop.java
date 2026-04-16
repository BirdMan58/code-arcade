package pieces;

import java.util.ArrayList;

import main.GamePanel;

public class Bishop extends Piece {

	public Bishop(int row, int col, boolean isWhite, GamePanel panel){
		super(row, col, isWhite, panel);
		type = PieceType.BISHOP;
		image = panel.setImg(type, isWhite);
	}

	@Override
	public ArrayList<Move> getMoves() {

		getPath(1, 1);
		getPath(1, -1);
		getPath(-1, -1);
		getPath(-1, 1);

		return moves;
	}
}
