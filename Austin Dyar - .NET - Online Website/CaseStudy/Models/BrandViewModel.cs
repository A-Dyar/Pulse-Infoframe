using Microsoft.AspNetCore.Mvc.Rendering;
using System.Collections.Generic;
using System.Linq;
using System;
using System.ComponentModel.DataAnnotations;

namespace CaseStudy.Models
{
    public class BrandViewModel
    {
        private List<Brand> _brands;
        public IEnumerable<Product> Products { get; set; }
        [Required]
        public int Qty { get; set; }
        public string SelectedProductId { get; set; }
        public string BrandName { get; set; }
        public int BrandId { get; set; }
        public IEnumerable<SelectListItem> GetBrands()
        {
            return _brands.Select(brand => new SelectListItem { Text = brand.Name, Value = brand.Id.ToString() });
        }
        public void SetBrands(List<Brand> brands)
        {
            _brands = brands;
        }
    }
}
