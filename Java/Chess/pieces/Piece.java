package pieces;

import java.awt.image.*;
import java.util.ArrayList;

import main.*;

public abstract class Piece {

	protected boolean isWhite;
	protected int row;
	protected int col;
	protected int x;
	protected int y;
	protected BufferedImage image;
	private Piece hittingPiece;
	public ArrayList<Move> moves;
	protected PieceType type;
	private GamePanel panel;
	
	public Piece(int row, int col, boolean isWhite, GamePanel panel) {
		this.isWhite = isWhite;
		this.row = row;
		this.col = col;
		this.x = getX(col);
		this.y = getY(row);
		this.moves = new ArrayList<>();
		this.panel = panel;
	}

	public int getX(int col) {
		return col * GamePanel.BOX_SIZE;
	}

	public int getY(int row) {
		return row * GamePanel.BOX_SIZE;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	public boolean getColor() {
		return isWhite;
	}

	public int getRow(int y) {
		if(panel.isFlipped())
			return 7 - (y / GamePanel.BOX_SIZE);
		else
			return y / GamePanel.BOX_SIZE;
	}

	public int getCol(int x) {
		if(panel.isFlipped())
			return 7 - (x / GamePanel.BOX_SIZE);
		else
			return x / GamePanel.BOX_SIZE;
	}

	public PieceType getType() {
		return type;
	} 

	public BufferedImage getImage() {
		return image;
	}

	public boolean isActive(int x, int y, boolean isWhite) {
		int activeRow = getRow(y);
		int activeCol = getCol(x);

		return (activeCol == col && activeRow == row && this.isWhite == isWhite);		
	}

	public void updatePosition (int targetRow, int targetCol) {
		this.x = getX(targetCol);
		this.y = getY(targetRow);

		this.row = targetRow;
		this.col = targetCol;
	}

	public Piece isHittingPiece(int targetRow, int targetCol) {
		for(Piece piece : Board.pieces) {
			if(piece.row == targetRow && piece.col == targetCol) {
				return piece;
			}
		}

		return null;
	}

	public ArrayList<Move> getMoves() {
		return null;
	}

	public boolean makeMove(int targetX, int targetY) {
		int targetRow = getRow(targetY);
		int targetCol = getCol(targetX);

		Move playerMove = new Move(targetRow, targetCol);
		hittingPiece = isHittingPiece(targetRow, targetCol);

		for(Move move : Board.moves) {
			if(playerMove.isSame(move)) {
				if(move.isEmpty) {
					Sounds.playSE(0);
					updatePosition(targetRow, targetCol);
					return true;
				} else if(move.isEnemy) {
					Board.pieces.remove(hittingPiece);
					Sounds.playSE(1);
					updatePosition(targetRow, targetCol);
					if(hittingPiece.getClass() == King.class) {
						Board.gameOver = true;
					}
					return true;
				} else if(move.isAlly) {
						break;
				}
			} 
		}					
		if(hittingPiece == null) {
			Sounds.playSE(2);
			return false;
		} else if(hittingPiece.getColor() == this.getColor()) {
			Board.activePiece = hittingPiece;
			if(Board.moves != null)
				Board.moves.clear();
			Board.moves = hittingPiece.getMoves();
			return false;
		}
		
		return false;
	}

	public boolean addMove(int mRow, int mCol) {
		if(isHittingPiece(mRow, mCol) != null) { 
			moves.add(new Move(mRow, mCol, this.isWhite, isHittingPiece(mRow, mCol).getColor()));
			return false;
		 } else {
			moves.add(new Move(mRow, mCol, isWhite, null));
			return true;
		}	
	}

	public void getPath(int xDirection, int yDirection) {
		int tempRow = row;
		int tempCol = col;
		
		while(tempRow >= 0 && tempRow <= 7 && tempCol >= 0 && tempCol <= 7) {
			tempRow += yDirection;
			tempCol += xDirection;
			
			if(!addMove(tempRow, tempCol))
				break;
		}
	}

}
