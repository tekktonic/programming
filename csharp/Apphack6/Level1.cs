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
    public class Level1 : ILevel
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
        private bool gameOver;
        private HighScoresWindow highScore;
        
        public Level1(Jump game)
        {
            this.game = game;
            this.blocks = new List<Block>();
            this.speed = 64;
            this.rng = new Random();
            this.spawnInterval = 200;
            this.tilNext = this.spawnInterval;
        }

        public void Init()
        {
            this.player = new Player(game, this, new Rectangle(512, -32, 32, 32));
            game.Components.Add(player);

            Block floor = new Block(game, this, new Rectangle(-32, 32, 1024 + 64, 32), Color.RoyalBlue, this.speed);
            blocks.Add(floor);
            game.Components.Add(floor);

            this.scoreText = new Text(game, "Score: " + this.points, new Vector2(0,0), Color.Blue);
            game.Components.Add(this.scoreText);

            this.highScore = new HighScoresWindow(game);
            game.Components.Add(this.highScore);
            
            music = this.game.Content.Load<SoundEffect>("bamboo");

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
                    this.game.level = new LevelM(game);
                    this.End();
                    return;
                }
            }
            this.scoreText.Content = "Score: " + this.points;
            this.ticks++;

            if (this.tilNext == 0)
            {
                
                Block b1 = new Block(game, this, new Rectangle(-32, -30, rng.Next(1024), 24), Color.RoyalBlue, this.speed);
                Block b2 = new Block(game, this, new Rectangle(b1.rect.X + b1.rect.Width + 64, -30, 1024, 24), Color.RoyalBlue, this.speed);

                b1.SetPartner(b2);
                this.blocks.Add(b1);
                this.blocks.Add(b2);
                this.game.Components.Add(b1);
                this.game.Components.Add(b2);

                this.tilNext = this.spawnInterval;
            }

            if (this.ticks % (200 * 5) == 0)
            {
                if (this.spawnInterval > 88)
                {
                    this.spawnInterval = (int)(this.spawnInterval * 0.90);
                    Console.WriteLine("Spawn interval is: " + this.spawnInterval);
                }


            }

            this.tilNext--;

            if (player.rect.X > 1024)
            {
                player.rect.X = 0 - player.rect.Width;
            }
            else if (player.rect.X + player.rect.Width < 0)
            {
                player.rect.X = 1024;
            }

            if (player.rect.Y > 1024)
            {
                if (!this.gameOver)
                {
                    this.gameOver = true;
                    this.highScore.SetStateInput(this.points, 0);
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