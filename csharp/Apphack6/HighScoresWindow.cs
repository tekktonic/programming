using System;
using Microsoft.Xna.Framework;
using System.Collections.Generic;
using System.IO;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace JumpGame
{
	public class HighScoresWindow : DrawableGameComponent
	{
		private const string FILEPATH = "Highscores.txt";
		private const string FILEPATH2 = "Highscores2.txt";
		private const string FILEPATH3 = "Highscores3.txt";
		private Keys[] keyArray;

		private Jump game;
		private Text gameText1, gameText2, enterNameText, nameText;
		private List<HighscoreEntry> highScores = new List<HighscoreEntry>();
		private Texture2D background1, background2, highscoreTile;
		private Texture2D nameBack1, nameBack2;
		private Vector2 position1, position2, namePos1, namePos2;
		private Keys lastKey;
		private int newScore = 0;
		private int curState = 0;
		private bool state1 = true;
		private bool firstInput = false;
		
		public HighScoresWindow(Jump game) : base(game)
		{
			this.game = game;
			position1 = new Vector2(312, 84);
			position2 = new Vector2(327, 99);
		}

		public bool Active
		{
			get;
			set;
		}
		
		protected override void LoadContent()
		{
//			Active = true;//For t esting.

			keyArray = new Keys[]
			{
				Keys.A, Keys.B, Keys.C, Keys.D, Keys.E, Keys.F, Keys.G, Keys.H, Keys.I, Keys.J, Keys.K, Keys.L, Keys.M,
				Keys.N, Keys.O, Keys.P, Keys.Q, Keys.R, Keys.S, Keys.T, Keys.U, Keys.V, Keys.W, Keys.X, Keys.Y, Keys.Z
			};

			LoadHighScores();
			background1 = CreateTexture(400, 600, game.graphics);
			background2 = CreateTexture(370, 570, game.graphics);
			nameBack1 = CreateTexture(400, 200, game.graphics);
			namePos1 = new Vector2(312, 284);
			nameBack2 = CreateTexture(370, 170, game.graphics);
			namePos2 = new Vector2(327, 299);
			highscoreTile = CreateTexture(370, 52, game.graphics);
			enterNameText = new Text(game, "ENTER YOUR NAME", new Vector2 (415, 310), Color.White);
			enterNameText.OtherLoadContent("HighJakarta_22");
			nameText = new Text(game, "Type Your Name", new Vector2 (415, 380), Color.White);
			nameText.OtherLoadContent("HighJakarta_22");
			gameText1 = new Text(game, "", new Vector2(), Color.White);
			gameText1.OtherLoadContent("HighJakarta_22");
			gameText2 = new Text(game, "", new Vector2 (), Color.White);
			gameText2.OtherLoadContent("HighJakarta_22");
		}

		public override void Update(GameTime gt)
		{
			if (!state1 || !Active)
			{
				Keys[] tKeys = Keyboard.GetState().GetPressedKeys();
				if (tKeys.Length == 1 && tKeys [0] == Keys.Enter && (lastKey == null || lastKey != Keys.Enter))
				{
					Active = false;
				}
				else if (tKeys.Length != 1)
				{
					lastKey = Keys.Add;
				}
				return;
			}
			
			KeyboardState state = Keyboard.GetState();
			Keys[] pressedKeys = state.GetPressedKeys();

			if (pressedKeys.Length == 1)
			{
				if (lastKey != pressedKeys[0])
				{
					lastKey = pressedKeys[0];

					if (pressedKeys[0] == Keys.Enter)
					{
						Console.WriteLine("Enter pressed");
						if (firstInput && nameText.Content.Length > 1)
						{
							Console.WriteLine("SWITCH HIGHSCORE STATES");
							highScores.Add(new HighscoreEntry (nameText.Content, newScore));
							highScores.Sort((s1, s2) => s2.Score.CompareTo(s1.Score));
							while (highScores.Count > 9)
								highScores.RemoveAt(highScores.Count - 1);
							SerializeHighScores();
							SetStateHighscore();
						}
					}
					else if (pressedKeys[0] == Keys.Back)
					{
						if (!firstInput)
						{
							firstInput = true;
							nameText.Content = "";
						}
						else
						{
							if (nameText.Content.Length > 0)
							{
								nameText.Content = nameText.Content.Substring(0, nameText.Content.Length - 1);
							}
						}
					}
					else if (pressedKeys[0] == Keys.Space)
					{
						if (!firstInput)
						{
							firstInput = true;
							nameText.Content = "";
						}
						else
						{
							nameText.Content += " ";

							if (nameText.Content.Length > 35)
							{
								nameText.Content = nameText.Content.Substring(0, 35);
							}
						}
					}
					else
					{
						for (int i = 0; i < keyArray.Length; i++)
						{
							if (keyArray [i] == lastKey)
							{
								if (!firstInput)
								{
									firstInput = true;
									nameText.Content = "";
								}

								nameText.Content += lastKey + "";

								break;
							}
						}
					}
				}
			}
			else
			{
				lastKey = Keys.Add;
			}
		}

		public override void Draw(GameTime gt)
		{
			if (!Active)
				return;

			if (state1)
				DrawStateOne(gt);
			else
				DrawStateTwo(gt);
		}

		public void SetStateInput(int score, int gameMode)
		{
			curState = gameMode < 3 ? gameMode : 0;
			LoadHighScores();
			newScore = score;
			Active = true;
			state1 = true;
			enterNameText.Content = "ENTER YOUR NAME";
			firstInput = false;
		}

		public void SetStateHighscore()
		{
			Active = true;
			state1 = false;
			enterNameText.Content = "ENTER YOUR NAME";
			firstInput = false;
		}

		private void DrawStateOne(GameTime gt)
		{
			game.batch.Begin();
			game.batch.Draw(nameBack1, namePos1, Color.Black);
			game.batch.Draw(nameBack2, namePos2, Color.Blue);
			enterNameText.InnerDraw(gt);
			nameText.InnerDraw(gt);
			game.batch.End();
		}

		private void DrawStateTwo(GameTime gt)
		{
			game.batch.Begin();
			game.batch.Draw(background1, position1, Color.Black);
			game.batch.Draw(background2, position2, Color.Blue);

			int stepY = 52;
			int stepX = 327;

			gameText1.Content = "HIGHSCORES";
			gameText1.Location = new Vector2(445, 135);
			gameText1.InnerDraw(gt);

			for (int index = 0; index < highScores.Count &&  index < 9; index++)
			{
				int curY = 149 + (stepY * (index + 1));
				game.batch.Draw(highscoreTile, new Vector2(stepX, curY), index % 2 == 0 ? Color.LightGreen : Color.Red);
				gameText1.Location = new Vector2(stepX + 25, curY + 10);
				gameText1.Content = (index + 1) + "  " + highScores[index].Score + "  " + highScores[index].Name;
				if (gameText1.Content.Length > 28)
					gameText1.Content = gameText1.Content.Substring(0, 28);
				gameText1.InnerDraw(gt);
			}


			game.batch.End();
		}

		private void LoadHighScores()
		{
			if (!File.Exists(FILEPATH))
			{
				return;
			}
				
			string[] data = null;

			highScores.Clear();

			if (curState == 0)
			{
				if (File.Exists(FILEPATH))
				{
					data = File.ReadAllLines(FILEPATH);
				}
			}
			else if (curState == 1)
			{
				if (File.Exists(FILEPATH2))
				{
					data = File.ReadAllLines(FILEPATH2);
				}
			}
			else
			{
				if (File.Exists(FILEPATH3))
				{
					data = File.ReadAllLines(FILEPATH3);
				}
			}

			char[] delimiter = new char[] { ':' };

			for (int dataIndex = 0; data != null && dataIndex < data.Length; dataIndex++)
			{
				string[] tData = data[dataIndex].Split(delimiter);

				if (tData.Length > 1)
					highScores.Add(new HighscoreEntry(tData[0], int.Parse(tData[1])));
			}

			highScores.Sort((s1, s2) => s2.Score.CompareTo(s1.Score));
		}

		private void SerializeHighScores()
		{
			List<String> data = new List<String>();

			foreach(HighscoreEntry entry in highScores)
			{
				data.Add(entry.Name + ":" + entry.Score);
			}
				
			if (curState == 0)
			{
				File.WriteAllLines(FILEPATH, data);
			}
			else if (curState == 1)
			{
				File.WriteAllLines(FILEPATH2, data);
			}
			else
			{
				File.WriteAllLines(FILEPATH3, data);
			}
		}

		private Texture2D CreateTexture(int width, int height, GraphicsDeviceManager g)
		{
			Texture2D tex = new Texture2D(g.GraphicsDevice, width, height);
			Color[] data = new Color[width*height];

			for (int i = 0; i < data.Length; ++i)
			{
				data [i] = Color.White;
			}

			tex.SetData(data);
			return tex;
		}
	}
}

