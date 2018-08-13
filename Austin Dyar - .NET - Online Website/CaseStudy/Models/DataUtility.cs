using System;
using System.Collections.Generic;
using System.Linq;

namespace CaseStudy.Models
{
    public class DataUtility
    {
        private AppDbContext _db;
        dynamic objectJson; // an element that is typed as dyanmic is assumed to support an operation
        public DataUtility(AppDbContext context)
        {
            _db = context;
        }
        public bool loadInformationFromFileToDb(string stringJson)
        {
            bool brandsLoaded = false;
            bool productsLoaded = false;
            try
            {
                objectJson = Newtonsoft.Json.JsonConvert.DeserializeObject(stringJson);
                brandsLoaded = loadBrands();
                productsLoaded = loadProducts();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            return brandsLoaded && productsLoaded;
        }

        private bool loadBrands()
        {
            bool loadedBrands = false;
            try
            {
                // clear out the old rows
                _db.Brands.RemoveRange(_db.Brands);
                _db.SaveChanges();
                List<String> allBrands = new List<string>();
                foreach(var node in objectJson)
                {
                    allBrands.Add(Convert.ToString(node["Brand"]));
                }
                // distinct will remove duplicates before we insert them into the db
                IEnumerable<String> brands = allBrands.Distinct<String>();
                foreach(string brandname in brands)
                {
                    Brand brand = new Brand();
                    brand.Name = brandname;
                    _db.Brands.Add(brand);
                    _db.SaveChanges();
                }
                loadedBrands = true;
            }
            catch(Exception ex)
            {
                Console.WriteLine("Error - " + ex.Message);
            }
            return loadedBrands;
        }

        private bool loadProducts()
        {
            bool loadedProducts = false;
            try
            {
                List<Brand> brands = _db.Brands.ToList();
                // clear out the old
                _db.Products.RemoveRange(_db.Products);
                _db.SaveChanges();
                string productid = "";
                int identity = 0;
                foreach (var node in objectJson)
                {
                    ++identity;
                    Product product = new Product();
                    product.Id = productid + Convert.ToString(identity);
                    product.CostPrice = Convert.ToDecimal(node["CostPrice"].Value);
                    product.Description = Convert.ToString(node["Description"].Value);
                    product.GraphicName = Convert.ToString(node["GraphicName"].Value);
                    product.MSRP = Convert.ToDecimal(node["MSRP"].Value);
                    product.ProductName = Convert.ToString(node["ProductName"].Value);
                    product.QtyOnBackOrder = Convert.ToInt32(node["QtyOnBackOrder"].Value);
                    product.QtyOnHand = Convert.ToInt32(node["QtyOnHand"].Value);
                    string brand = Convert.ToString(node["Brand"].Value);
                    // add the FK here
                    foreach (Brand bra in brands)
                    {
                        if(bra.Name == brand)
                        {
                            product.Brand = bra;
                        }
                    }
                    _db.Products.Add(product);
                    _db.SaveChanges();
                }
                loadedProducts = true;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error - " + ex.Message);
            }
            return loadedProducts;
        }
    }
}
