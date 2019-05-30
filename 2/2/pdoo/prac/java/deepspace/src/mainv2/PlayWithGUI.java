/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mainv2;

import Deepspace.GameUniverse;
import View.GUI.MainWindow;
import View.View;
import controller.Controllerv2;

/**
 *
 * @author diagmatrix
 */
public class PlayWithGUI {
    public static void main(String[] args) {
        GameUniverse model = new GameUniverse();
        View view = MainWindow.getInstance();
        Controllerv2 controller = Controllerv2.getInstance();
        controller.setModelView(model,view);
        controller.start();
    }
}
