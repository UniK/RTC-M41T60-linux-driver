//Notwendige Header
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/i2c.h>
#include <linux/bcd.h>
#include <linux/rtc.h>
#include <asm/uaccess.h>

//I2C Treiber: behandelt alle an den Bus angeschlossenen Ger�te
static struct i2c_driver rtc_driver;
//I2C Client: steht f�r ein einzlnes Device (hier:RTC)
static struct i2c_client *rtc_client;
//I2C Client Adressen: enth�lt alle Adreesen von angeschlossenen Ger�ten
static unsigned short normal_addr[] = { 0x68, I2C_CLIENT_END };

//Struktur h�lt die Adressen der Kernelfunktionen
static struct file_operations fops;

//�ffnet den Treiber
static int rtc_open( struct inode *geraetedatei, struct file *instanz );
//schliessen des Treibers
static int rtc_close(struct inode *geraetdedatei, struct file *instanz);


//lesen von Daten aus dem Treiber
static ssize_t rtc_read(struct file *instanz, char *user, size_t count, loff_t *offset );
// schreiben von Daten in den Treiber
static ssize_t rtc_write( struct file *instanz, char __user *userbuffer, size_t count, loff_t *offset );
//Universalschnittstelle f�r die Ein- und Ausgabe, anhand des Parameters: cmd wird die entsprechende Aktion ausgef�hrt
static int rtc_ioctl( struct inode *inode, struct file *instanz, unsigned int cmd, unsigned long arg);


//f�gt den Client zum Bus hinzu
static int rtc_probe(struct i2c_adapter *adapter, int addr, int kind);
//registriert den Bus beim Kernel
static int rtc_attach(struct i2c_adapter *adap);
//entfernt den Bus vom Kernel
static int rtc_detach(struct i2c_client *client);


// Wird ausgefuert beim Laden des Modules.
static int __init rtc_module_init(void);
//Wird ausgefuert beim Entladen des Modules.
static void __exit rtc_module_exit(void);

module_init(rtc_module_init);
module_exit(rtc_module_exit);


//Module-Informationen.
MODULE_AUTHOR("Klaus Musterman <musterr@uni-kassel.de>");
MODULE_DESCRIPTION("Beschreibung");
MODULE_LICENSE("GPL");


