using Microsoft.AspNetCore.Mvc;
using CaseStudy.Models;
using System.Collections.Generic;
using CaseStudy.Utils;
using System;

namespace CaseStudy.Controllers
{
    public class BrandController : Controller
    {
        AppDbContext _db;
        public BrandController(AppDbContext context)
        {
            _db = context;
        }
        public IActionResult Index(BrandViewModel vm)
        {
            // Only build the catalogue once
            if (HttpContext.Session.Get<List<Brand>>(SessionVars.Brands) == null)
            {
                // no session information so let's go to the database
                try
                {
                    BrandModel categoryModel = new BrandModel(_db);
                    // now load the categories
                    List<Brand> categories = categoryModel.GetAll();
                    HttpContext.Session.Set<List<Brand>>(SessionVars.Brands, categories);
                    vm.SetBrands(categories);
                }
                catch (Exception ex)
                {
                    ViewBag.Message = "Catalogue Problem - " + ex.Message;
                }
            }
            else
            {
                // no need to go back to the database as information is already in the session
                vm.SetBrands(HttpContext.Session.Get<List<Brand>>(SessionVars.Brands));
                ProductModel itemModel = new ProductModel(_db);
                vm.Products = itemModel.GetAllByBrand(vm.BrandId);
            }
            return View(vm);
        }
        
        public IActionResult SelectBrand(BrandViewModel vm)
        {
            BrandModel brandModel = new BrandModel(_db);
            ProductModel productModel = new ProductModel(_db);
            List<Product> products = productModel.GetAllByBrand(vm.BrandId);
            List<ProductViewModel> productViewModels = new List<ProductViewModel>();
            if(products.Count > 0)
            {
                foreach(Product product in products)
                {
                    ProductViewModel productViewModel = new ProductViewModel();
                    productViewModel.Qty = 0;
                    productViewModel.QtyOnBackOrder = product.QtyOnBackOrder;
                    productViewModel.QtyOnHand = product.QtyOnHand;
                    productViewModel.Description = product.Description;
                    productViewModel.Id = product.Id;
                    productViewModel.BrandName = brandModel.GetName(product.BrandId);
                    productViewModel.GraphicName = product.GraphicName;
                    productViewModel.CostPrice = product.CostPrice;
                    productViewModel.MSRP = product.MSRP;
                    productViewModel.BrandId = product.BrandId;
                    productViewModel.ProductName = product.ProductName;
                    productViewModels.Add(productViewModel);
                }
                ProductViewModel[] myItems = productViewModels.ToArray();
                HttpContext.Session.Set<ProductViewModel[]>(SessionVars.Items, myItems);
            }
            vm.SetBrands(HttpContext.Session.Get<List<Brand>>(SessionVars.Brands));
            return View("Index", vm);
        }
        [HttpPost]
        public ActionResult SelectItem(BrandViewModel vm)
        {
            Dictionary<string, object> cart;
            if (HttpContext.Session.Get<Dictionary<string, Object>>(SessionVars.Cart) == null)
            {
                cart = new Dictionary<string, object>();
            }
            else
            {
                cart = HttpContext.Session.Get<Dictionary<string, object>>(SessionVars.Cart);
            }
            ProductViewModel[] items = HttpContext.Session.Get<ProductViewModel[]>(SessionVars.Items);
            String retMsg = "";
            foreach (ProductViewModel item in items)
            {
                if (item.Id == vm.SelectedProductId)
                {
                    if (vm.Qty > 0) // update only selected item
                    {
                        item.Qty = vm.Qty;
                        retMsg = vm.Qty + " - item(s) Added!";
                        cart[item.Id] = item;
                    }
                    else
                    {
                        item.Qty = 0;
                        cart.Remove(item.Id);
                        retMsg = "item(s) Removed!";
                    }
                    vm.BrandId = item.BrandId;
                    break;
                }
            }
            ViewBag.AddMessage = retMsg;
            HttpContext.Session.Set<Dictionary<string, Object>>(SessionVars.Cart, cart);
            vm.SetBrands(HttpContext.Session.Get<List<Brand>>(SessionVars.Brands));
            return PartialView("AddToCartPartial");
        }
    }
}