package main;

import java.awt.Color;
import javax.imageio.*;
import java.awt.image.*;
import java.io.*;

public class Config {

	public static int boardSize = 416;
	public static Color black = new Color(63, 71, 89);
	public static Color white = new Color(207, 201, 187);
	public static Color active = new Color(241, 250, 140);
	public static Color path = new Color(80, 250, 123, 125);
	public static Color enemy = new Color(255, 85, 85, 190);
	public static Color ally = new Color(77, 77, 77, 125);
	public static boolean isWhite = true;
	public static boolean soundOn = true;
	public static boolean flippingOn = true;
	public static BufferedImage whiteSheet, blackSheet;
	static {
		try {
			whiteSheet = ImageIO.read(new File("main/res/classicwhite.png"));
			blackSheet = ImageIO.read(new File("main/res/classicblack.png"));
				
		} catch(IOException e) {
			e.printStackTrace();
		}
	}	

	public Config() {
		//default values
	}

}
