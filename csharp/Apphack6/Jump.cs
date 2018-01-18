using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace JumpGame
{

    public delegate void KeyboardStateEventHandler(KeyboardStateEventArgs e);
    
    public class Jump : Game
    {
		private static GameTime time;
		private const int SCREENWIDTH = 1024;
		private const int SCREENHEIGHT = 768;
		private const bool FULLSCREEN = false;

        public GraphicsDeviceManager graphics;
        public SpriteBatch batch;

        public ILevel level;
        private ILevel lastLevel;
        public KeyboardStateEventHandler KeyboardEvent;
        
        public Jump()
        {
            graphics = new GraphicsDeviceManager(this);
            graphics.PreferredBackBufferWidth = SCREENWIDTH;
            graphics.PreferredBackBufferHeight = SCREENHEIGHT;
            Content.RootDirectory = "Content";
        }

		public static GameTime Time
		{
			get { return time; }
		}

        protected override void Initialize()
        {
//			Block block = new Block(this, new Rectangle(100, 500, 800, 200), Color.Blue, 20);
//            player = new Player(this, new Rectangle(512, 384, 32, 32));
//            this.Components.Add(player);
  //          this.Components.Add(block);
    //        this.blocks.Add(block);
            this.level = new LevelM(this);
            this.lastLevel = this.level;
            this.level.Init();
            base.Initialize();

        }

        protected override void LoadContent()
        {
            batch = new SpriteBatch(GraphicsDevice);
            base.LoadContent();
        }


        protected virtual void OnKeyboard(KeyboardStateEventArgs args)
		{
			if (KeyboardEvent != null)
				KeyboardEvent (args);
		}
        
        protected override void Update(GameTime gt)
        {
			time = gt;

            if (level != lastLevel)
            {
                level.Init();
                lastLevel = level;
            }
            
            KeyboardState keystate = Keyboard.GetState ();
            
            OnKeyboard (new KeyboardStateEventArgs(keystate));
            level.Tick();
            base.Update(gt);
        }

        protected override void Draw(GameTime gt)
        {
            GraphicsDevice.Clear(Color.HotPink);


            base.Draw(gt);
        }
        
       public static void Main()
       {
           System.Console.WriteLine("Test");
           try
           {
               using (Jump game = new Jump())
                   game.Run();
           }catch (EntryPointNotFoundException e)
           {
           }
       }
    }

    public class KeyboardStateEventArgs : EventArgs {
		public KeyboardStateEventArgs(KeyboardState state) : base()
		{
			keyState = state;
		}
		public KeyboardState keyState { get; set;}
	}
    
}
