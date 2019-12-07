package il.co.ilrd.vending_machine;

<<<<<<< HEAD
import java.security.Timestamp;
import java.util.Collection;
import java.util.Objects;
=======
import java.time.LocalTime;
import java.util.List;
import java.util.function.Consumer;
>>>>>>> 3a5965980602f92687ed9fbda828b8f264b99e00


/**
 * 
 * @author Shieber
 * @reviewer Daniel
 * @version 1.3
 * @since 1.0
 *
 */
public class VendingMachine {

<<<<<<< HEAD
    private State state;
    private int currBalance;
    private Collection<Product> products;
    private ViewModule view;
    private Thread thread;
    private boolean active;
    private Timestamp startTime;

    public VendingMachine(Collection<Product> items, ViewModule view) {
        this.products = items;
        this.view = view;
        state = State.INIT;
        active = true;
        
        thread = new Thread ( () -> {

            while (active) {
                state.timeout(this);
                try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
            }
        });
    }

    /**
     * Initializes and invokes VendingMachine to begin state.
     */
    public void start() {
        state.init(this);
    }

    /**
     * Shutdown the VendingMachine.
     */
    public void shutDown() {
        state.shutDown(this);
    }

    /**
     * Insert money into machine.
     * @param coinValue inserted for transaction.
     */
    public void insertCoin(int coinValue) {
        state.insertCoin(this, coinValue);
    }

    /**
     * Chooses product to buy.
     * @param chosen product.
     * invalid product will not have effect,
     * error message will be displayed in ViewModel.
     */
    public void chooseProduct(Product chosen) {
    }

    /**
     * cancels current transaction, and flushes change
     */
    public void cancel() {
        state.cancel(this);
    }

    private enum State {
        INIT{
            @Override
            void init(VendingMachine vm) { /*FIXME init start time */
            }
            
            @Override
            void handleCurrentState (VendingMachine vm) {
            	
            }
            
        },

        IDLE {
        	@Override
        	void insertCoin(VendingMachine vm, int coinValue) {
        	}

        	@Override
        	void handleCurrentState (VendingMachine vm) {
        		
        	}
        	
        },

        COLLECTING_MONEY {
            
        	@Override
            void insertCoin(VendingMachine vm, int coinValue) {
            }

            @Override
            void chooseProduct(VendingMachine vm, Product product) {
            }

            void cancel (VendingMachine vm) {
            }

            @Override
            void timeout(VendingMachine vm) {
            }
            
            @Override
            void handleCurrentState (VendingMachine vm) {
            	
            }
            
        },

        TRANSACTION_COMPLETE {
            @Override
            void timeout(VendingMachine vm) {
            }
            
            @Override
            void handleCurrentState (VendingMachine vm) {
            	
            }
            
        };

        /*
         *  Will initialize Vending machine, change to waitForProduct state
         * @param vm - current Vending Machine
         */
        void init(VendingMachine vm) {

        }
        
        /*
         *  Will shut down Vending machine, change change active flag to false
         * @param vm - current Vending Machine
         */
        void shutDown(VendingMachine vm) {

        }
        /*
         * Handles payment transaction, increases current balance,
         * changes state to WAIT_FOR_PRODUCT if there is sufficient balance.
         */
        void insertCoin(VendingMachine vm, int money) {

        }

        /*
         * Changes selected product in vm, changes state to waitForMoney
         */
        void chooseProduct(VendingMachine vm, Product product) {

        }

        /*
         * @param vm cancels current transaction,
         *  changes state to waitForProduct
         */
        void cancel(VendingMachine vm){
        }

        /*
         * @param vm 
         *  handles timeout event 
         */
        void timeout (VendingMachine vm) {
        	
        }
        
        /*
         * @param vm 
         * sets start time to current time of state transition
         */
        abstract void handleCurrentState (VendingMachine vm);
    }

    public static class Product {
        private String name;
        private int price;

        Product(String name, int price) {
            this.price = price;
            this.name = name;
        }

		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + ((name == null) ? 0 : name.hashCode());
=======
	private State state = State.INIT;
	private double currBalance;
	private List<Product> products;
	private Consumer<String> view;
	private Thread thread;
	private boolean active = true;
	private LocalTime startTime;
	private static final int THREAD_INTERVAL_MS = 1000;

	public VendingMachine(List<Product> items, Consumer<String> view) {
		this.products = items;
		this.view = view;
	}
	
	private void printMenu() {
		for (Product p : products) {
			System.out.print("Product\t: " + p.name + "\n" +
							 "Price\t: " + p.price + "\n\n");
		}
	}

	/**
	 * Initializes and invokes VendingMachine.
	 */
	public void start() {

		thread = new Thread(() -> {

			while (active) {
				state.timeout(this);
				try {
					Thread.sleep(THREAD_INTERVAL_MS);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		});

		thread.start();

		state.init(this);
	}

	/**
	 * Shuts down the Vending Machine.
	 */
	public void shutDown() {
		state.shutDown(this);
	}

	/**
	 * Insert money into machine.
	 * 
	 * @param coinValue inserted for transaction.
	 */
	public void insertCoin(double coinValue) {
		state.insertCoin(this, coinValue);
	}

	/**
	 * Chooses product to buy.
	 * 
	 * @param productIndex product. invalid product will not have effect, error message
	 *               will be displayed in ViewModel.
	 */
	public void chooseProduct(int productIndex) {
		state.chooseProduct(this, productIndex);
	}

	/**
	 * cancels current transaction, and flushes change
	 */
	public void cancel() {
		state.cancel(this);
	}
	
	/**
	 * Enum which represents the state in which the Vending Mahcine is in.
	 */
	private enum State {
		INIT {
			@Override
			void init(VendingMachine vm) {
				setState(vm, IDLE);
			}

			@Override
			void setState(VendingMachine vm, State state) {
				vm.state = state;
			}
		},

		IDLE {
			@Override
			void insertCoin(VendingMachine vm, double coinValue) {
				vm.printMenu();
				COLLECTING_MONEY.insertCoin(vm, coinValue);
			}

			@Override
			void setState(VendingMachine vm, State state) {
				vm.startTime = LocalTime.now();
				vm.state = state;
			}

		},

		COLLECTING_MONEY {

			@Override
			void insertCoin(VendingMachine vm, double coinValue) {
				vm.currBalance += coinValue;

				setState(vm, COLLECTING_MONEY);
			}

			@Override
			void chooseProduct(VendingMachine vm, int productIndex) {
				vm.startTime = LocalTime.now();

				if (productIndex < 0 ||
						vm.products.size() - 1 < productIndex) {
					vm.view.accept("Product not available");

					setState(vm, COLLECTING_MONEY);
					return;
				}

				else if (vm.currBalance <
									vm.products.get(productIndex).price) {
					vm.view.accept("Insufficient funds. current balance is "
															 + vm.currBalance);
					setState(vm, COLLECTING_MONEY);
					return;

				} else {
					vm.currBalance -= vm.products.get(productIndex).price;
					vm.view.accept("Dispensing product " +
										vm.products.get(productIndex).name);
					setState(vm, TRANSACTION_COMPLETE);
				}
			}

			void cancel(VendingMachine vm) {

				vm.state.returnChange(vm);

				setState(vm, IDLE);

			}

			@Override
			void timeout(VendingMachine vm) {
				if (vm.startTime.plusSeconds(CM_TO).isBefore(LocalTime.now())) {
					vm.state.cancel(vm);
				}
			}

			@Override
			void setState(VendingMachine vm, State state) {
				vm.startTime = LocalTime.now();
				vm.state = state;
			}

		},

		TRANSACTION_COMPLETE {
			@Override
			void timeout(VendingMachine vm) {

				if (vm.startTime.plusSeconds(TC_TO).isBefore(LocalTime.now())) {

					vm.view.accept("Transaction complete");

					vm.state.returnChange(vm);

					setState(vm, IDLE);
				}
			}

			@Override
			void setState(VendingMachine vm, State state) {
				vm.startTime = LocalTime.now();
				vm.state = state;
			}
		};

		/*
		 * Will initialize Vending machine, change to COLLECTING_MONEY state
		 * 
		 * @param vm - current Vending Machine
		 */
		void init(VendingMachine vm) {

		}

		/*
		 * Shuts down Vending machine, changes active flag to false
		 * 
		 * @param vm - current Vending Machine
		 */
		void shutDown(VendingMachine vm) {
			vm.active = false;

			try {
				vm.thread.join();
			} catch (InterruptedException e) {
				System.err.println("error joining thread");
			}
		}

		/*
		 * Handles payment transaction, increases current balance, changes
		 * state to COLLECTING_MONEY if there is sufficient balance.
		 * 
		 * @param vm - current Vending Machine
		 * @param coin - value of coin.
		 */
		void insertCoin(VendingMachine vm, double coin) {

		}

		/*
		 * Changes selected product in vm, changes state to TRAN
		 */
		void chooseProduct(VendingMachine vm, int productIndex) {
		}

		/*
		 * @param vm cancels current transaction, changes state to waitForProduct
		 */
		void cancel(VendingMachine vm) {
		}

		/*
		 * @param vm handles timeout event
		 */
		void timeout(VendingMachine vm) {
		}

		/*
		 * @param vm sets start time to current time of state transition
		 */
		abstract void setState(VendingMachine vm, State state);

		void returnChange(VendingMachine vm) {
			vm.view.accept("flushing " + vm.currBalance + " in change.");
			vm.currBalance = 0;
		}

		/* Timeouts for Transaction Complete and Collecting Money states */
		private final static int TC_TO = 5;
		private final static int CM_TO = 10;
	}

	public static class Product {
		private String name;
		private int price;
		final static private int PRIME = 31;

		Product(String name, int price) {
			this.price = price;
			this.name = name;
		}

		@Override
		public int hashCode() {
			int result = 1;
			result = PRIME * result + ((name == null) ? 0 : name.hashCode());
>>>>>>> 3a5965980602f92687ed9fbda828b8f264b99e00
			return result;
		}

		@Override
		public boolean equals(Object obj) {
<<<<<<< HEAD
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			Product other = (Product) obj;
			if (name == null) {
				if (other.name != null)
					return false;
			} else if (!name.equals(other.name))
				return false;
			return true;
		}

    }

=======

			if (obj instanceof Product) {
				Product other = (Product) obj;
				if (name == null) {
					if (other.name != null) {
						return false;
					}
					else if (!name.equals(other.name)) {
						return false;
					}
				}
			}
			return true;
		}
	}
>>>>>>> 3a5965980602f92687ed9fbda828b8f264b99e00
}