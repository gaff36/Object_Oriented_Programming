public interface HexGame
{
	public int playComputer();
	public boolean didPlayerOneWin(Integer check[], int x, int y, int limit);
	public boolean didPlayerTwoWin(Integer check [], int x, int y, int limit);
	public void saveGame(String fileName);
	public boolean loadGame(String fileName);
}