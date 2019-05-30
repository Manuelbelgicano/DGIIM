/**
 * @author Manuel Gachs Ballegeer
 */
package View;

import controller.Controllerv2;
import java.util.ArrayList;

public interface View {
    public void updateView();
    public void showView();
    public ArrayList<String> getNames();
    public void setController(Controllerv2 c);
    public boolean confirmExitMessage();
}
