package main;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;

import java.awt.FlowLayout;

class Main {

	public static void main(String[] args) {
		ImageIcon logo = new ImageIcon("main/res/logo.jpg");

		JFrame frame = new JFrame("Chess Bird");
		frame.setIconImage(logo.getImage());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false);
		frame.setLayout(new FlowLayout());
		frame.setSize(416, 416);
		frame.setLocationRelativeTo(null);
		JPanel gamePanel = new GamePanel();
		frame.add(gamePanel);
		frame.pack();
		frame.setVisible(true);

	}
}
