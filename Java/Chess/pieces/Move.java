package pieces;

import main.GamePanel;

public class Move {

	public int row;
	public int col;
	public boolean isEnemy = false;
	public boolean isAlly = false;
	public boolean isEmpty = false;

	public Move(int row, int col, boolean activeColor, Boolean pieceColor) {
		this.row = row;
		this.col =col;

		if(pieceColor == null)
			isEmpty = true;
		else if(activeColor == pieceColor)
			isAlly = true;
		else
			isEnemy = true;
	}

	public Move(int row, int col) {
		this.row = row;
		this.col = col;
	}

	public boolean isSame(Move move) {
		return (this.row == move.row && this.col == move.col);
	}

	public int getX() {	
		return col * GamePanel.BOX_SIZE;
	}

	public int getY() {
		return row * GamePanel.BOX_SIZE;
	}
}
