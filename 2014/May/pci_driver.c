/*
 * =====================================================================================
 *
 *       Filename:  pci_driver.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/28/2013 03:15:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
MODULE_LICENSE("Dual BSD/GPL");

/* This is a test driver for a specific e1000e type
 *
 * Ethernet controller: Intel Corporation 82579LM Gigabit Network Connection 
 */
static DEFINE_PCI_DEVICE_TABLE(test_e1000_pci_tbl) = {
	{ PCI_VDEVICE(INTEL, 0x1502), 0 },
	{ 0, 0, 0, 0, 0, 0, 0 }	/* terminate list */
};
MODULE_DEVICE_TABLE(pci, test_e1000_pci_tbl);

char test_e1000_driver_name[] = "e1000e_test";

/* Register offset, copyied from hw.h */
#define E1000_RCTL      0x00100 /* Rx Control - RW */

/* Receive Control, copyied from defines.h */
#define E1000_RCTL_EN   0x00000002    /* enable */

struct priv_data {
	void __iomem *hw_addr;
};

static int test_e1000_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int err, bar;
	u16 vendor, device;
	unsigned long mmio_start, mmio_end, mmio_len, mmio_flags;
	void *ioaddr;
	u32 rctl;
	struct priv_data *priv;
	int pm_cap;

	/* access the config space */
	pci_read_config_word(pdev, PCI_VENDOR_ID, &vendor);
	pci_read_config_word(pdev, PCI_DEVICE_ID, &device);
	pr_info("The vendor_id is %x, the device_id is %x\n", vendor, device);

	err = pci_enable_device_mem(pdev);

	/* IO BARs */
	bar = pci_select_bars(pdev, IORESOURCE_IO);
	pr_info("Availale IO  BARs are 0x%x\n", bar);

	/* Request a IO region */
	err = pci_request_selected_regions_exclusive(pdev,
			bar, test_e1000_driver_name);

	/* MEM BARs */
	bar = pci_select_bars(pdev, IORESOURCE_MEM);
	pr_info("Availale MEM BARs are 0x%x\n", bar);

	/* Request a MEM region */
	err = pci_request_selected_regions_exclusive(pdev,
			bar, test_e1000_driver_name);

	mmio_start = pci_resource_start(pdev, 0);
	mmio_end   = pci_resource_end(pdev, 0);
	mmio_len   = pci_resource_len(pdev, 0);
	mmio_flags = pci_resource_flags(pdev, 0);
	pr_info("Resource 0: start at 0x%lx with lenght %lu\n",
			mmio_start, mmio_len);

	/* Allocate the dev private data structure */
	priv = kzalloc(sizeof(struct priv_data), GFP_KERNEL);
	if (!priv) {
		err = -1;
		goto fail1;
	}

	pci_set_drvdata(pdev, priv);

	/* ioremap MMIO region */
	ioaddr = ioremap(mmio_start, mmio_len);
	if (!ioaddr) {
		err = -1;
		pr_info("Couldn't ioremap MMIO\n");
		goto fail2;
	}
	priv->hw_addr = ioaddr;
	pr_info("Mapped resource 0x%lx to 0x%p\n", mmio_start, ioaddr);

	/* MMIO r/w, enable the receive function */
	rctl = readl(ioaddr + E1000_RCTL);
	pr_info("Address 0x%p contains 0x%08x\n", ioaddr, rctl);

	/* ATTENTION!!!
	 *     Read SPEC before do the write.
	 *     This may cause undefined behavior.
	 */
	writel(rctl | E1000_RCTL_EN, ioaddr + E1000_RCTL);
	rctl = readl(ioaddr + E1000_RCTL);
	pr_info(" -- after enablement        0x%08x\n", rctl);

	pm_cap = pci_find_capability(pdev, PCI_CAP_ID_PM);
	pr_info("The Power Management Capability Position is %d\n", pm_cap);

	return err;

fail2:
	kfree(priv);

fail1:
	pci_release_selected_regions(pdev, 
			pci_select_bars(pdev, IORESOURCE_IO|IORESOURCE_MEM));

	pci_disable_device(pdev);
	return err;
}

static void test_e1000_remove(struct pci_dev *pdev)
{
	struct priv_data *priv;

	priv = pci_get_drvdata(pdev);

	iounmap(priv->hw_addr);
	kfree(priv);

	pci_release_selected_regions(pdev, 
			pci_select_bars(pdev, IORESOURCE_IO|IORESOURCE_MEM));

	pci_disable_device(pdev);
}

static struct pci_driver test_e1000e_driver = {
	.name     = test_e1000_driver_name,
	.id_table = test_e1000_pci_tbl,
	.probe    = test_e1000_probe,
	.remove   = test_e1000_remove,
};

static int pci_driver_test_init(void)
{
	int ret;
	pr_info("--- A test driver for pci device ---\n");
	ret = pci_register_driver(&test_e1000e_driver);

        return ret;
}
static void pci_driver_test_exit(void)
{
	pci_unregister_driver(&test_e1000e_driver);
}
module_init(pci_driver_test_init);
module_exit(pci_driver_test_exit);
