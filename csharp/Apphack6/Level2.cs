using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace JumpGame
{
    public class Level2 : ILevel
    {
        List<Block> blocks;
        Player player;
        Jump game;
        private int points;
        private Text scoreText;
        private int ticks;
        private int spawnInterval;
        private int tilNext;
        private int speed;
        private Random rng;
        private SoundEffect music;
        private SoundEffectInstance musicInstance;
        private int narrowness;
        private bool gameOver;
        private HighScoresWindow highScore;
        
        public Level2(Jump game)
        {
            this.game = game;
            this.blocks = new List<Block>();
            this.speed = -128;
            this.rng = new Random();
            this.spawnInterval = 64;
            this.tilNext = this.spawnInterval;
            this.narrowness = 16;
            this.points = 0;
        }

        public void Init()
        {
            this.player = new Player(game, this, new Rectangle(1024 - 40, 768 - 64, 32, 32));
            game.Components.Add(player);

            Block floor = new Block(game, this, new Rectangle(1024 - 48, 768 - 32, 48, 1024), Color.Cyan, this.speed, 0);

            blocks.Add(floor);
            game.Components.Add(floor);

            this.scoreText = new Text(game, "Score: " + this.points, new Vector2(0,0), Color.Blue);
            game.Components.Add(this.scoreText);

            this.highScore = new HighScoresWindow(game);
            game.Components.Add(this.highScore);
            
            music = this.game.Content.Load<SoundEffect>("home_at_last");

            musicInstance = music.CreateInstance();
            musicInstance.IsLooped = true;
            musicInstance.Play();
        }

        public List<Block> GetBlocks()
        {
            return blocks;
        }
        
        public void Tick()
        {
            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
            {
                if (!this.highScore.Active)
                {
                    this.game.level = new LevelM(this.game);
                    this.End();
                    return;
                }
            }
            this.scoreText.Content = "Score: " + this.points;
            this.ticks++;

            if (this.tilNext <= 0)
            {
                
                Block newBlock = new Block(game, this, new Rectangle(1024, 760
                                                                     - rng.Next((int)((50.0/this.spawnInterval) * 100))
                                                                     , 48 - rng.Next(this.narrowness), 768),
                                           Color.Cyan, this.speed, 0);
                blocks.Add(newBlock);
                game.Components.Add(newBlock);
                this.tilNext = rng.Next(100) + 50 - ((-this.speed) / 8);
                this.spawnInterval = this.tilNext;
            }

            if (this.ticks % 300 == 0)
            {
                if (this.speed > -256)
                {
                    this.speed -= 64;
                }
                if (this.narrowness < 44)
                    this.narrowness += 4;
                else
                    this.narrowness = 44;

            }
            this.tilNext--;

            if (player.rect.Y > 1024 || (player.rect.X + player.rect.Width) < 0)
            {
                if (!this.gameOver)
                {
                    this.gameOver = true;
                    this.highScore.SetStateInput(this.points, 1);
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
            this.game.Components.Remove(this.highScore);
            this.musicInstance.Stop();
        }
        
        public void AddPoints(int points)
        {
            this.points += points;
        }
   } 
}