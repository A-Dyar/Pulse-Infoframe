using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using System;
using CaseStudy.Utils;
using CaseStudy.Models;
using System.Collections.Generic;

namespace CaseStudy.Controllers
{
    public class CartController : Controller
    {
        AppDbContext _db;
        public CartController(AppDbContext context)
        {
            _db = context;
        }
        public IActionResult Index()
        {
            return View();
        }
        public ActionResult ClearCart() // clear out current items
        {
            HttpContext.Session.Remove(SessionVars.Cart);
            HttpContext.Session.Set<String>(SessionVars.Message, "Cart Cleared");
            return Redirect("/Home");
        }
        // Add the cart, pass the session variable info to the db
        public ActionResult AddCart()
        {
            CartModel model = new CartModel(_db);
            Tuple<int, int> retVals;
            string retMessage = "";
            try
            {
                Dictionary<string, object> cartItems = HttpContext.Session.Get<Dictionary<string, object>>(SessionVars.Cart);
                retVals = model.AddCart(cartItems, HttpContext.Session.GetString(SessionVars.User));
                if (retVals.Item1 > 0) // Cart Added
                {
                    retMessage = "Cart " + retVals.Item1 + " Created!" + ((retVals.Item2 == 1) ?  " Some goods were backordered." : "") ;
                }
                else // problem
                {
                    retMessage = "Cart not added, try again later";
                }
            }
            catch (Exception ex) // big problem
            {
                retMessage = "Cart was not created, try again later! - " + ex.Message;
            }
            HttpContext.Session.Remove(SessionVars.Cart); // clear out current cart once persisted
            HttpContext.Session.SetString(SessionVars.Message, retMessage);
            return Redirect("/Home");
        }
        public IActionResult List()
        {
            // they can't list Carts if they're not logged on
            if (HttpContext.Session.GetString(SessionVars.User) == null)
            {
                return Redirect("/Login");
            }
            return View("List");
        }

        [Route("[action]")]
        public IActionResult GetCarts()
        {
            CartModel model = new CartModel(_db);
            return Ok(model.GetAll(HttpContext.Session.GetString(SessionVars.User)));
        }

        [Route("[action]/{tid:int}")]
        public IActionResult GetCartDetails(int tid)
        {
            CartModel model = new CartModel(_db);
            return Ok(model.GetCartDetails(tid, HttpContext.Session.GetString(SessionVars.User)));
        }
    }
}