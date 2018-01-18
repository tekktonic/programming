using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;



namespace JumpGame
{
    public class Player : JumpSprite
    {
        private int xSpeed, ySpeed;
        private bool ground;
        private float direction;
        
        public Player(Jump game, ILevel level, Rectangle rect) : base(game)
        {
            this.game = game;
            this.rect = rect;
            this.level = level;
            this.game.KeyboardEvent += KeyboardUpdate;
        }

        protected override void LoadContent()
        {
            this.tex = this.game.Content.Load<Texture2D>("Player");

            this.origin = new Vector2(this.tex.Width / 2, this.tex.Height / 2);
        }

        public void KeyboardUpdate(KeyboardStateEventArgs args)
        {
            KeyboardState st = args.keyState;

            if (st.IsKeyDown(Keys.Left))
            {
                this.xSpeed = -5;
            }
            else if (st.IsKeyDown(Keys.Right))
            {
                this.xSpeed = 5;
            }
            else
            {
                this.xSpeed = 0;
            }

            if (st.IsKeyDown(Keys.Up))
            {
                if (this.ground)
                {
                    this.ySpeed = -24;
                    this.ground = false;
                }
            }
            else if (st.IsKeyDown(Keys.Down))
            {
                this.ySpeed = 5;
            }
        }


        public override void Draw(GameTime gt)
        {
//            base.Draw(gt);
            Vector2 position = new Vector2((int)(rect.X + (rect.Width / 2)), (int)(rect.Y + (rect.Height / 2)));

            SpriteBatch sprite = this.game.batch;
            sprite.Begin();
            sprite.Draw (tex, position, new Rectangle(0, 0, tex.Width, tex.Height), Color.White, direction,
                         new Vector2(tex.Width / 2, tex.Height / 2),
                         1.0f, SpriteEffects.None, 0);
            sprite.End();

        }
        public override void Update(GameTime gt)
        {

            foreach (Block b in this.level.GetBlocks())
            {
                Rectangle other = b.rect;
                
                Rectangle leftRect = new Rectangle(this.rect.X + this.xSpeed, this.rect.Y + 8, 16, this.rect.Height - 16);
                Rectangle rightRect = new Rectangle((this.rect.X + this.rect.Width) + this.xSpeed - 16, this.rect.Y + 8, 16, this.rect.Height - 16);
                Rectangle topRect = new Rectangle(this.rect.X + 8, this.rect.Y + this.ySpeed, this.rect.Width - 16, 16);
                Rectangle bottomRect = new Rectangle(this.rect.X + 6, this.rect.Y  + this.rect.Height + this.ySpeed, this.rect.Width - 12, 16);
                
                if (JumpSprite.RectCollides(rightRect, other))
                {
                    this.rect.X = b.rect.X - this.rect.Width - 1;
                    this.xSpeed = 0;
                }
                else if (JumpSprite.RectCollides(leftRect, other))
                {
                    this.rect.X = b.rect.X + b.rect.Width + 1;
                    this.xSpeed = 0;
                }

                if (JumpSprite.RectCollides(topRect, other))
                {
                    this.rect.Y = b.rect.Y + b.rect.Height + 1;
                    this.ySpeed = 0;
                }
                else if (JumpSprite.RectCollides(bottomRect, other))
                {
                    this.rect.Y = b.rect.Y - this.rect.Height;
                    this.ySpeed = 0;
                    this.direction = 0.0f;
                    b.Hit();
                    if (!Keyboard.GetState().IsKeyDown(Keys.Up))
                        this.ground = true;
                    
                    this.xSpeed += b.GetXSpeed(gt);
                }
            }

            if (this.rect.Y < 0)
            {
                this.rect.Y = 0;
                this.ySpeed = 0;
            }
            if (this.ySpeed < 24)
                this.ySpeed += 1;

            if (!this.ground)
            {
                this.direction += this.xSpeed;
            }
            
            this.rect.X += this.xSpeed;
            this.rect.Y += this.ySpeed;
        }
    }
}