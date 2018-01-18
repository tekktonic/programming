using System;

namespace JumpGame
{
	public class HighscoreEntry
	{
		public HighscoreEntry(string name, int score)
		{
			Name = name;
			Score = score;
		}

		public string Name
		{
			get;
			set;
		}

		public int Score
		{
			get;
			set;
		}
	}
}
