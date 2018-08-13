using System;
using System.Collections.Generic;
using System.Linq;
using Newtonsoft.Json;
namespace CaseStudy.Models
{
    public class CartModel
    {
        private AppDbContext _db;
        public CartModel(AppDbContext ctx)
        {
            _db = ctx;
        }
        public Tuple<int,int> AddCart(Dictionary<string, object> items, string user)
        {
            int cartId = -1;
            int backOrder = -1;
            using (_db)
            {
                // we need a transaction as multiple entities involved
                using (var _trans = _db.Database.BeginTransaction())
                {
                    try
                    {
                        Cart cart = new Cart();
                        cart.UserId = user;
                        cart.OrderDate = System.DateTime.Now;
                        // calculate the totals and then add the cart row to the table
                        foreach (var key in items.Keys)
                        {
                            ProductViewModel item = JsonConvert.DeserializeObject<ProductViewModel>(Convert.ToString(items[key]));
                            if (item.Qty <= item.QtyOnHand)
                            {
                                cart.OrderAmount += item.MSRP * item.Qty;
                            }
                            else if (item.Qty > item.QtyOnHand)
                            {
                                cart.OrderAmount += item.MSRP * item.QtyOnHand;
                            }
                        }
                        _db.Cart.Add(cart);
                        _db.SaveChanges();
                        // then add each item to the cartitems table
                        foreach (var key in items.Keys)
                        {
                            ProductViewModel item = JsonConvert.DeserializeObject<ProductViewModel>(Convert.ToString(items[key]));
                            if (item.Qty <= item.QtyOnHand)
                            {

                                CartItems cItem = new CartItems();
                                cItem.QtySold = item.Qty;
                                cItem.QtyBackOrdered = 0;
                                cItem.SellingPrice = cart.OrderAmount;
                                cItem.QtyOrdered = item.Qty;
                                cItem.CartId = cart.Id;
                                cItem.ProductId = item.Id;

                                cItem.Product = _db.Products.FirstOrDefault(p => p.Id == item.Id);
                                cItem.Product.QtyOnHand = cItem.QtySold;

                                _db.CartItems.Add(cItem);
                                _db.SaveChanges();
                            }
                            else if (item.Qty > item.QtyOnHand)
                            {
                                CartItems cItem = new CartItems();
                                cItem.QtySold = item.QtyOnHand;
                                cItem.QtyBackOrdered = item.Qty - item.QtyOnHand;
                                cItem.SellingPrice = cart.OrderAmount;
                                cItem.QtyOrdered = item.Qty;
                                cItem.CartId = cart.Id;
                                cItem.ProductId = item.Id;
                                
                                cItem.Product = _db.Products.FirstOrDefault(p => p.Id == item.Id);
                                cItem.Product.QtyOnHand = 0;
                                cItem.Product.QtyOnBackOrder += cItem.QtyBackOrdered;

                                _db.CartItems.Add(cItem);
                                _db.SaveChanges();

                                backOrder = 1;
                            }
                        }
                        // test trans by uncommenting out these 3 lines
                        //int x = 1;
                        //int y = 0;
                        //x = x / y;
                        _trans.Commit();
                        cartId = cart.Id;
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex.Message);
                        _trans.Rollback();
                    }
                }
            }
            return Tuple.Create(cartId, backOrder);
        }
        public List<Cart> GetAll(string User)
        {
            return _db.Cart.Where(cart => cart.UserId == User).ToList<Cart>();
        }

        public List<CartViewModel> GetCartDetails(int tid, string uid)
        {
            List<CartViewModel> allDetails = new List<CartViewModel>();
            // LINQ way of doing INNER JOINS
            var results = from t in _db.Set<Cart>()
                          join ti in _db.Set<CartItems>() on t.Id equals ti.CartId
                          join mi in _db.Set<Product>() on ti.ProductId equals mi.Id
                          where (t.UserId == uid && t.Id == tid)
                          select new CartViewModel
                          {
                              CartId = t.Id,
                              ProductId = mi.Id,
                              ProductName = mi.ProductName,
                              UserId = uid,
                              QtyOrdered = ti.QtyOrdered,
                              QtySold = ti.QtySold,
                              Description = mi.Description,
                              OrderAmount = t.OrderAmount,
                              OrderTax = Math.Round(t.OrderAmount * .13m, 2),
                              QtyOnBackOrder = ti.QtyBackOrdered,
                              MSRP = mi.MSRP,
                              DateCreated = t.OrderDate.ToString("yyyy/MM/dd - hh:mm tt")
                          };
            allDetails = results.ToList<CartViewModel>();
            return allDetails;
        }
    }
}