using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Audio;

namespace JumpGame
{
	public class Level3 : ILevel
	{
		private List<Block> blocks = new List<Block>();
		private Player player;
		private Jump game;
		private Random random = new Random();
		private int points;
		private int speed = 150;
		private int leftoverSpeed = 0;
		private int elapsedTime = 0;
		private int speedUp = 2000;

		private int yVariance = 40; //220
		private int xVariance = 40; //220
		private int xVarianceStep = 10;
		private int yVarianceStep = 10;

		private int widthMax = 300; 
		private int widthVariance = 10; //50 - 268
		private int widthVarianceStep = 10;

		private SoundEffect music;
		private SoundEffectInstance musicInstance;

		private bool gameOver;
		private HighScoresWindow highScore;
//		private int points;
		private Text scoreText;

		public Level3(Jump game)
		{
			this.game = game;
		}
	
		public void Init()
		{
			speed = 5;//1000 / speed;
			player = new Player(game, this, new Rectangle(512, 0, 32, 32));
			game.Components.Add(player);
			Block floor = new Block(game, this, new Rectangle(0, 736, 1024, 32), Color.SpringGreen, 0, 0);//740
			blocks.Add(floor);

			game.Components.Add(floor);

			CheckNextBlockSpawn();

			this.highScore = new HighScoresWindow(game);
			game.Components.Add(this.highScore);

			this.scoreText = new Text(game, "Score: " + this.points, new Vector2(0,0), Color.Blue);
			game.Components.Add(this.scoreText);

			music = this.game.Content.Load<SoundEffect>("super_secret_tune");

			musicInstance = music.CreateInstance();
			musicInstance.IsLooped = true;
			musicInstance.Play();

			points = 0;
		}

		public void Tick()
		{
			if (Keyboard.GetState().IsKeyDown(Keys.Escape))
			{
				if (!this.highScore.Active)
				{
                    this.game.level = new LevelM(game);
                    this.End();
                    return;
				}
			}

			if (gameOver)
			{
				return;
			}

			this.scoreText.Content = "Score: " + this.points;

			elapsedTime += Jump.Time.ElapsedGameTime.Milliseconds;
			int totalTime = leftoverSpeed + Jump.Time.ElapsedGameTime.Milliseconds;
			int movePixels = -(totalTime / speed);
			leftoverSpeed = totalTime % speed;
			bool movePlayer = false;

			if (movePixels < -3)
			{
				points++;
			}

			foreach (Block block in blocks)
			{
				block.rect = new Rectangle (block.rect.X + movePixels, block.rect.Y, block.rect.Width, block.rect.Height);
				if (!movePlayer && block.rect.Intersects(player.rect))
				{
					movePlayer = true;
					player.rect = new Rectangle(player.rect.X + movePixels, player.rect.Y, player.rect.Width, player.rect.Height);
				}
			}

			if (elapsedTime > speedUp)
			{
				elapsedTime = elapsedTime % speedUp;
				NextStep();
				Console.WriteLine("NEXT STEP!");
			}

			CheckNextBlockSpawn();

			if (player.rect.Y > 1024 || (player.rect.X + player.rect.Width) < 0)
			{
				if (!this.gameOver)
				{
					player.Enabled = false;
					this.gameOver = true;
					this.highScore.SetStateInput(this.points, 2);

					while(blocks.Count > 0)
					{
						game.Components.Remove(blocks [0]);
						blocks.RemoveAt(0);
					}
					this.game.Components.Remove(this.player);
					this.game.Components.Remove(this.scoreText);
					this.musicInstance.Stop();
				}
			}
		}

		public void End()
		{
			this.game.Components.Remove(this.player);
            this.game.Components.Remove(this.scoreText);
            
            foreach (Block b in this.blocks)
            {
                this.game.Components.Remove(b);
            }
            this.musicInstance.Stop();
		}

		public void AddPoints(int points)
		{
			this.points += points;
		}

		public List<Block> GetBlocks()
		{
			return blocks;
		}

		private void SpawnNextBlock()
		{
			Block lastBlock = blocks[blocks.Count - 1];
			int nextWidth = random.Next(widthMax - widthVariance, widthMax);
			Rectangle tRect = new Rectangle (XRange(lastBlock.rect.X + lastBlock.rect.Width), YRange(lastBlock.rect.Y), nextWidth, 32);//YRange(lastBlock.rect.Y)
			Block block = new Block (game, this, tRect, Color.SpringGreen, 0);
			blocks.Add(block);
			game.Components.Add(block);
		}

		private int YRange(int lastY)
		{
			int newY;

			if (yVariance < 300)
			{
				newY = random.Next(lastY - yVariance, lastY + yVariance);
			}
			else
			{
				newY = random.Next(lastY - 300, lastY + 300);
			}

			if (newY < 64)
				newY = 64;
			else if (newY > 736)
				newY = 736;
			return newY;
		}

		private int XRange(int lastX)
		{
			int newX;

			if (xVariance < 300)
			{
				newX = lastX + random.Next(xVariance/2, xVariance);
			}
			else
			{
				newX = lastX + random.Next(xVariance/2, 300);
			}

			return newX;
		}

		private void NextStep()
		{
			yVariance += yVarianceStep; //220
			if (yVariance > 300)
				yVariance = 300;
			
			xVariance += xVarianceStep; //220
			if (xVariance > 300)
				xVariance = 300;
				
			widthVariance += widthVarianceStep;//50; //50 - 268
			if (widthVariance > 268)
				widthVariance = 268;
		}

		private void CheckNextBlockSpawn()
		{
			while (blocks [blocks.Count - 1].rect.X < 1024)
			{
				SpawnNextBlock();
			}
		}
	}
}

